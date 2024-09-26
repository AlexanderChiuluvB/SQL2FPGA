// number of overlays (w/o fusion): 4 
// number of overlays (w/ fusion): 4 
#include <sys/time.h> 
#include <algorithm> 
#include <cstring> 
#include <fstream> 
#include <iomanip> 
#include <iostream> 
#include <sstream> 
#include <climits> 
#include <unordered_map> 
#include "table_dt.hpp" 
#include "utils.hpp" 
#include "tpch_read_2.hpp" 
#include "gqe_api.hpp" 

#include "cfgFunc_q13.hpp" 
#include "q13.hpp" 

const int PU_NM = 8; 
#define TREE_COUNT 16
#define LOG_LEAF_COUNT 4
#define BANK_OFFSET 0
#define RECORD_IN_BYTES 8
#define INIT_SORTED_CHUNK 2
#define SORTED_CHUN_POST_P1 4
#define COARSE_BATCH_SIZE 4096

// Number of HBM PCs required
#define MAX_HBM_PC_COUNT 32
#define PC_NAME(n) n | XCL_MEM_TOPOLOGY
const int pc[MAX_HBM_PC_COUNT] = {
    PC_NAME(0),  PC_NAME(1),  PC_NAME(2),  PC_NAME(3),  PC_NAME(4),  PC_NAME(5),  PC_NAME(6),  PC_NAME(7),
    PC_NAME(8),  PC_NAME(9),  PC_NAME(10), PC_NAME(11), PC_NAME(12), PC_NAME(13), PC_NAME(14), PC_NAME(15),
    PC_NAME(16), PC_NAME(17), PC_NAME(18), PC_NAME(19), PC_NAME(20), PC_NAME(21), PC_NAME(22), PC_NAME(23),
    PC_NAME(24), PC_NAME(25), PC_NAME(26), PC_NAME(27), PC_NAME(28), PC_NAME(29), PC_NAME(30), PC_NAME(31)};





int main(int argc, const char* argv[]) { 
    std::cout << "\n------------ TPC-H Query Test -------------\n"; 
    ArgParser parser(argc, argv); 
    std::string xclbin_path; 
    if (!parser.getCmdOption("-xclbin", xclbin_path)) { 
        std::cout << "ERROR: xclbin path is not set!\n"; 
        return 1; 
    } 
    std::string xclbin_path_h; 
    if (!parser.getCmdOption("-xclbin_h", xclbin_path_h)) { 
        std::cout << "ERROR: xclbin_h path is not set!\n"; 
        return 1; 
    } 
    std::string xclbin_path_a; 
    if (!parser.getCmdOption("-xclbin_a", xclbin_path_a)) { 
        std::cout << "ERROR: xclbin_a path is not set!\n"; 
        return 1; 
    } 

    std::string xclbin_path_s; 
    if (!parser.getCmdOption("-xclbin_s", xclbin_path_s)) { 
        std::cout << "ERROR: xclbin_s path is not set!\n"; 
        return 1; 
    } 

    std::string in_dir; 
    if (!parser.getCmdOption("-in", in_dir) || !is_dir(in_dir)) { 
        std::cout << "ERROR: input dir is not specified or not valid.\n"; 
        return 1; 
    } 
    int num_rep = 1; 
    std::string num_str; 
    if (parser.getCmdOption("-rep", num_str)) { 
        try { 
            num_rep = std::stoi(num_str); 
        } catch (...) { 
            num_rep = 1; 
        } 
    } 
    if (num_rep > 20) { 
        num_rep = 20; 
        std::cout << "WARNING: limited repeat to " << num_rep << " times\n."; 
    } 
    int scale = 1; 
    std::string scale_str; 
    if (parser.getCmdOption("-c", scale_str)) { 
        try { 
            scale = std::stoi(scale_str); 
        } catch (...) { 
            scale = 1; 
        } 
    } 
    std::cout << "NOTE:running query #13\n."; 
    std::cout << "NOTE:running in sf" << scale << " data\n"; 

    int32_t lineitem_n = SF1_LINEITEM; 
    int32_t supplier_n = SF1_SUPPLIER; 
    int32_t nation_n = SF1_NATION; 
    int32_t order_n = SF1_ORDERS; 
    int32_t customer_n = SF1_CUSTOMER; 
    int32_t region_n = SF1_REGION; 
    int32_t part_n = SF1_PART; 
    int32_t partsupp_n = SF1_PARTSUPP; 
    if (scale == 30) { 
        lineitem_n = SF30_LINEITEM; 
        supplier_n = SF30_SUPPLIER; 
        nation_n = SF30_NATION; 
        order_n = SF30_ORDERS; 
        customer_n = SF30_CUSTOMER; 
        region_n = SF30_REGION; 
        part_n = SF30_PART; 
        partsupp_n = SF30_PARTSUPP; 
    } 
    // ********************************************************** // 
    // Get CL devices. 
    std::vector<cl::Device> devices = xcl::get_xil_devices(); 
    cl::Device device_h = devices[0]; 
    // Create context_h and command queue for selected device 
    cl::Context context_h(device_h); 
    cl::CommandQueue q_h(context_h, device_h, CL_QUEUE_PROFILING_ENABLE | CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE); 
    std::string devName_h = device_h.getInfo<CL_DEVICE_NAME>(); 
    std::cout << "Selected Device " << devName_h << "\n"; 
    cl::Program::Binaries xclBins_h = xcl::import_binary_file(xclbin_path_h); 
    std::vector<cl::Device> devices_h; 
    devices_h.push_back(device_h); 
    cl::Program program_h(context_h, devices_h, xclBins_h); 


    cl::Device device_a = devices[1]; 
    // Create context_a and command queue for selected device 
    cl::Context context_a(device_a); 
    cl::CommandQueue q_a(context_a, device_a, CL_QUEUE_PROFILING_ENABLE | CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE); 
    std::string devName_a = device_a.getInfo<CL_DEVICE_NAME>(); 
    std::cout << "Selected Device " << devName_a << "\n"; 
    cl::Program::Binaries xclBins_a = xcl::import_binary_file(xclbin_path_a); 
    std::vector<cl::Device> devices_a; 
    devices_a.push_back(device_a); 
    cl::Program program_a(context_a, devices_a, xclBins_a); 

    // Create context_sort and command queue for selected device, reuse devices[0]
    #ifdef TOPSORT
    cl::Program::Binaries xclBins_s = xcl::import_binary_file(xclbin_path_s); 
    cl::Program program_s(context_a, devices_a, xclBins_s); 
    #endif
    // ****************************** Tables **************************** // 
    Table tbl_Sort_TD_0263_output("tbl_Sort_TD_0263_output", 6100000, 2, "");
    tbl_Sort_TD_0263_output.allocateHost();    
    Table tbl_Aggregate_TD_1609_output_preprocess("tbl_Aggregate_TD_1609_output_preprocess", -1, 16, "");
    tbl_Aggregate_TD_1609_output_preprocess.allocateHost();
    Table tbl_Aggregate_TD_1609_output("tbl_Aggregate_TD_1609_output", -1, 2, "");
    tbl_Aggregate_TD_1609_output.allocateHost();
    Table tbl_Aggregate_TD_2946_output_preprocess("tbl_Aggregate_TD_2946_output_preprocess", -1, 16, "");
    tbl_Aggregate_TD_2946_output_preprocess.allocateHost();
    Table tbl_Aggregate_TD_2946_output("tbl_Aggregate_TD_2946_output", -1, 1, "");
    tbl_Aggregate_TD_2946_output.allocateHost();
    Table tbl_JOIN_LEFTANTI_TD_3654_output_preprocess("tbl_JOIN_LEFTANTI_TD_3654_output_preprocess", 1531000, 2, "");
    tbl_JOIN_LEFTANTI_TD_3654_output_preprocess.allocateHost();
    Table tbl_JOIN_LEFTANTI_TD_3654_output("tbl_JOIN_LEFTANTI_TD_3654_output", 1531000, 2, "");
    tbl_JOIN_LEFTANTI_TD_3654_output.allocateHost();
    Table tbl_JOIN_INNER_TD_0691_output("tbl_JOIN_INNER_TD_0691_output", 1480133, 3, "");
    tbl_JOIN_INNER_TD_0691_output.allocateHost();
    Table tbl_SerializeFromObject_TD_4820_input;
    tbl_SerializeFromObject_TD_4820_input = Table("customer", customer_n, 1, in_dir);
    tbl_SerializeFromObject_TD_4820_input.addCol("c_custkey", 4);
    tbl_SerializeFromObject_TD_4820_input.allocateHost();
    tbl_SerializeFromObject_TD_4820_input.loadHost();
    Table tbl_Filter_TD_470_output("tbl_Filter_TD_470_output", 6100000, 2, "");
    tbl_Filter_TD_470_output.allocateHost();
    Table tbl_SerializeFromObject_TD_59_input;
    tbl_SerializeFromObject_TD_59_input = Table("order", order_n, 3, in_dir);
    tbl_SerializeFromObject_TD_59_input.addCol("o_orderkey", 4);
    tbl_SerializeFromObject_TD_59_input.addCol("o_custkey", 4);
    tbl_SerializeFromObject_TD_59_input.addCol("o_comment", TPCH_READ_O_CMNT_MAX+1);
    tbl_SerializeFromObject_TD_59_input.allocateHost();
    tbl_SerializeFromObject_TD_59_input.loadHost();
    // ********************** Allocate Device Buffer ******************** // 
    tbl_Aggregate_TD_1609_output_preprocess.allocateDevBuffer(context_a, 33);
    tbl_JOIN_LEFTANTI_TD_3654_output.allocateDevBuffer(context_a, 32);
    tbl_Aggregate_TD_2946_output_preprocess.allocateDevBuffer(context_a, 33);
    tbl_Aggregate_TD_2946_output.allocateDevBuffer(context_a, 32);
    tbl_JOIN_LEFTANTI_TD_3654_output_preprocess.allocateDevBuffer(context_h, 32);
    tbl_JOIN_INNER_TD_0691_output.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_4820_input.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_470_output.allocateDevBuffer(context_h, 32);
    
    #ifdef TOPSORT
    // Allocate Buffer in Global Memory
    std::vector<cl::Buffer> buffer_0(TREE_COUNT);
    std::vector<cl::Buffer> buffer_1(TREE_COUNT);
    uint64_t byte_per_chan = elem_per_chan * RECORD_IN_BYTES;
    std::cout << "Bytes per channel is " << byte_per_chan << '\n';

    cl_mem_ext_ptr_t inBufExt[TREE_COUNT];
    cl_mem_ext_ptr_t outBufExt[TREE_COUNT];
    for (i = 0; i < TREE_COUNT; i++) {
        inBufExt[i].obj = tbl_Aggregate_TD_1609_output.data.data() + elem_per_chan * i;
        inBufExt[i].param = 0;
        inBufExt[i].flags = ( BANK_OFFSET + (2*i) ) | XCL_MEM_TOPOLOGY;

        outBufExt[i].obj = tbl_Sort_TD_0263_output.data.data() + elem_per_chan * i;
        outBufExt[i].param = 0;
        outBufExt[i].flags = ( BANK_OFFSET + (2*i+1) ) | XCL_MEM_TOPOLOGY;
    }
    for (i = 0; i < TREE_COUNT; i++) {
        OCL_CHECK(err, buffer_0[i] = cl::Buffer(context_h, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE | CL_MEM_EXT_PTR_XILINX,
                byte_per_chan, &inBufExt[i], &err));
        OCL_CHECK(err, buffer_1[i] = cl::Buffer(context_h, CL_MEM_USE_HOST_PTR | CL_MEM_READ_WRITE | CL_MEM_EXT_PTR_XILINX,
                byte_per_chan, &outBufExt[i], &err));
    }
    #endif
    
    
    // ****************************** Config **************************** // 
    AggrCfgCmd cfg_Aggregate_TD_1609_cmds;
    cfg_Aggregate_TD_1609_cmds.allocateHost();
    get_cfg_dat_Aggregate_TD_1609_gqe_aggr(cfg_Aggregate_TD_1609_cmds.cmd);
    cfg_Aggregate_TD_1609_cmds.allocateDevBuffer(context_a, 32);
    AggrCfgCmd cfg_Aggregate_TD_1609_cmds_out;
    cfg_Aggregate_TD_1609_cmds_out.allocateHost();
    cfg_Aggregate_TD_1609_cmds_out.allocateDevBuffer(context_a, 33);
    AggrCfgCmd cfg_Aggregate_TD_2946_cmds;
    cfg_Aggregate_TD_2946_cmds.allocateHost();
    get_cfg_dat_Aggregate_TD_2946_gqe_aggr(cfg_Aggregate_TD_2946_cmds.cmd);
    cfg_Aggregate_TD_2946_cmds.allocateDevBuffer(context_a, 32);
    AggrCfgCmd cfg_Aggregate_TD_2946_cmds_out;
    cfg_Aggregate_TD_2946_cmds_out.allocateHost();
    cfg_Aggregate_TD_2946_cmds_out.allocateDevBuffer(context_a, 33);
    cfgCmd cfg_JOIN_LEFTANTI_TD_3654_cmds;
    cfg_JOIN_LEFTANTI_TD_3654_cmds.allocateHost();
    get_cfg_dat_JOIN_LEFTANTI_TD_3654_gqe_join (cfg_JOIN_LEFTANTI_TD_3654_cmds.cmd);
    cfg_JOIN_LEFTANTI_TD_3654_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_INNER_TD_0691_cmds;
    cfg_JOIN_INNER_TD_0691_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_0691_gqe_join (cfg_JOIN_INNER_TD_0691_cmds.cmd);
    cfg_JOIN_INNER_TD_0691_cmds.allocateDevBuffer(context_h, 32);
    // *************************** Kernel Setup ************************* // 
    bufferTmp buftmp_h(context_h); 
    buftmp_h.initBuffer(q_h); 
    AggrBufferTmp buftmp_a(context_a); 
    buftmp_a.BufferInitial(q_a); 
    std::cout << std::endl; 
    AggrKrnlEngine krnl_Aggregate_TD_1609;
    krnl_Aggregate_TD_1609 = AggrKrnlEngine(program_a, q_a, "gqeAggr");
    krnl_Aggregate_TD_1609.setup(tbl_Aggregate_TD_2946_output, tbl_Aggregate_TD_1609_output_preprocess, cfg_Aggregate_TD_1609_cmds, cfg_Aggregate_TD_1609_cmds_out, buftmp_a);
    AggrKrnlEngine krnl_Aggregate_TD_2946;
    krnl_Aggregate_TD_2946 = AggrKrnlEngine(program_a, q_a, "gqeAggr");
    krnl_Aggregate_TD_2946.setup(tbl_JOIN_LEFTANTI_TD_3654_output, tbl_Aggregate_TD_2946_output_preprocess, cfg_Aggregate_TD_2946_cmds, cfg_Aggregate_TD_2946_cmds_out, buftmp_a);
    krnlEngine krnl_JOIN_LEFTANTI_TD_3654;
    krnl_JOIN_LEFTANTI_TD_3654 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_LEFTANTI_TD_3654.setup(tbl_SerializeFromObject_TD_4820_input, tbl_JOIN_INNER_TD_0691_output, tbl_JOIN_LEFTANTI_TD_3654_output_preprocess, cfg_JOIN_LEFTANTI_TD_3654_cmds, buftmp_h);
    krnlEngine krnl_JOIN_INNER_TD_0691;
    krnl_JOIN_INNER_TD_0691 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_0691.setup(tbl_SerializeFromObject_TD_4820_input, tbl_Filter_TD_470_output, tbl_JOIN_INNER_TD_0691_output, cfg_JOIN_INNER_TD_0691_cmds, buftmp_h);
    #ifdef TOPSORT
    krnl_sorter = krnlEngine(program_s, q_a, "merge_sort_complete");
    // setup kernel
    int nargs=0;
    OCL_CHECK(err, err = krnl_sorter.setArg(nargs++, byte_per_chan));
    OCL_CHECK(err, err = krnl_sorter.setArg(nargs++, num_pass));
    for (i = 0; i < TREE_COUNT; i++) {
        OCL_CHECK(err, err = krnl_sorter.setArg(nargs++, buffer_0[i]));
        OCL_CHECK(err, err = krnl_sorter.setArg(nargs++, buffer_1[i]));
    }
    #endif

    // ************************** Transfer Engine *********************** // 
    transEngine trans_Aggregate_TD_1609;
    trans_Aggregate_TD_1609.setq(q_a);
    trans_Aggregate_TD_1609.add(&(cfg_Aggregate_TD_1609_cmds));
    transEngine trans_Aggregate_TD_1609_out;
    trans_Aggregate_TD_1609_out.setq(q_a);
    q_a.finish();
    transEngine trans_Aggregate_TD_2946;
    trans_Aggregate_TD_2946.setq(q_a);
    trans_Aggregate_TD_2946.add(&(cfg_Aggregate_TD_2946_cmds));
    transEngine trans_Aggregate_TD_2946_out;
    trans_Aggregate_TD_2946_out.setq(q_a);
    q_a.finish();
    transEngine trans_JOIN_LEFTANTI_TD_3654;
    trans_JOIN_LEFTANTI_TD_3654.setq(q_h);
    trans_JOIN_LEFTANTI_TD_3654.add(&(cfg_JOIN_LEFTANTI_TD_3654_cmds));
    trans_JOIN_LEFTANTI_TD_3654.add(&(tbl_SerializeFromObject_TD_4820_input));
    transEngine trans_JOIN_LEFTANTI_TD_3654_out;
    trans_JOIN_LEFTANTI_TD_3654_out.setq(q_h);
    q_h.finish();
    transEngine trans_JOIN_INNER_TD_0691;
    trans_JOIN_INNER_TD_0691.setq(q_h);
    trans_JOIN_INNER_TD_0691.add(&(cfg_JOIN_INNER_TD_0691_cmds));
    trans_JOIN_INNER_TD_0691.add(&(tbl_SerializeFromObject_TD_4820_input));
    q_h.finish();
    // ****************************** Events **************************** // 
    std::vector<cl::Event> events_h2d_wr_Aggregate_TD_1609;
    std::vector<cl::Event> events_d2h_rd_Aggregate_TD_1609;
    std::vector<cl::Event> events_Aggregate_TD_1609;
    events_h2d_wr_Aggregate_TD_1609.resize(1);
    events_d2h_rd_Aggregate_TD_1609.resize(1);
    events_Aggregate_TD_1609.resize(1);
    std::vector<cl::Event> events_grp_Aggregate_TD_1609;
    std::vector<cl::Event> prev_events_grp_Aggregate_TD_1609;
    std::vector<cl::Event> events_h2d_wr_Aggregate_TD_2946;
    std::vector<cl::Event> events_d2h_rd_Aggregate_TD_2946;
    std::vector<cl::Event> events_Aggregate_TD_2946;
    events_h2d_wr_Aggregate_TD_2946.resize(1);
    events_d2h_rd_Aggregate_TD_2946.resize(1);
    events_Aggregate_TD_2946.resize(1);
    std::vector<cl::Event> events_grp_Aggregate_TD_2946;
    std::vector<cl::Event> prev_events_grp_Aggregate_TD_2946;
    std::vector<cl::Event> events_h2d_wr_JOIN_LEFTANTI_TD_3654;
    std::vector<cl::Event> events_d2h_rd_JOIN_LEFTANTI_TD_3654;
    std::vector<cl::Event> events_JOIN_LEFTANTI_TD_3654;
    events_h2d_wr_JOIN_LEFTANTI_TD_3654.resize(1);
    events_d2h_rd_JOIN_LEFTANTI_TD_3654.resize(1);
    events_JOIN_LEFTANTI_TD_3654.resize(1);
    std::vector<cl::Event> events_grp_JOIN_LEFTANTI_TD_3654;
    std::vector<cl::Event> prev_events_grp_JOIN_LEFTANTI_TD_3654;
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_0691;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_0691;
    std::vector<cl::Event> events_JOIN_INNER_TD_0691;
    events_h2d_wr_JOIN_INNER_TD_0691.resize(1);
    events_d2h_rd_JOIN_INNER_TD_0691.resize(1);
    events_JOIN_INNER_TD_0691.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_0691;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_0691;
    #ifdef
    cl::Event sortKrnlEvent;
    #endif
    // **************************** Operations ************************** // 
    struct timeval tv_r_s, tv_r_e; 
    gettimeofday(&tv_r_s, 0); 

    struct timeval tv_r_Filter_4_323_s, tv_r_Filter_4_323_e;
    gettimeofday(&tv_r_Filter_4_323_s, 0);
    SW_Filter_TD_470(tbl_SerializeFromObject_TD_59_input, tbl_Filter_TD_470_output);
    gettimeofday(&tv_r_Filter_4_323_e, 0);

    struct timeval tv_r_JOIN_INNER_0_116_s, tv_r_JOIN_INNER_0_116_e;
    gettimeofday(&tv_r_JOIN_INNER_0_116_s, 0);
    trans_JOIN_INNER_TD_0691.add(&(tbl_Filter_TD_470_output));
    trans_JOIN_INNER_TD_0691.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_0691), &(events_h2d_wr_JOIN_INNER_TD_0691[0]));
    events_grp_JOIN_INNER_TD_0691.push_back(events_h2d_wr_JOIN_INNER_TD_0691[0]);
    krnl_JOIN_INNER_TD_0691.run(0, &(events_grp_JOIN_INNER_TD_0691), &(events_JOIN_INNER_TD_0691[0]));
    gettimeofday(&tv_r_JOIN_INNER_0_116_e, 0);

    struct timeval tv_r_JOIN_LEFTANTI_3_20_s, tv_r_JOIN_LEFTANTI_3_20_e;
    gettimeofday(&tv_r_JOIN_LEFTANTI_3_20_s, 0);
    prev_events_grp_JOIN_LEFTANTI_TD_3654.push_back(events_h2d_wr_JOIN_INNER_TD_0691[0]);
    trans_JOIN_LEFTANTI_TD_3654.host2dev(0, &(prev_events_grp_JOIN_LEFTANTI_TD_3654), &(events_h2d_wr_JOIN_LEFTANTI_TD_3654[0]));
    events_grp_JOIN_LEFTANTI_TD_3654.push_back(events_h2d_wr_JOIN_LEFTANTI_TD_3654[0]);
    events_grp_JOIN_LEFTANTI_TD_3654.push_back(events_JOIN_INNER_TD_0691[0]);
    krnl_JOIN_LEFTANTI_TD_3654.run(0, &(events_grp_JOIN_LEFTANTI_TD_3654), &(events_JOIN_LEFTANTI_TD_3654[0]));
    
    trans_JOIN_LEFTANTI_TD_3654_out.add(&(tbl_JOIN_LEFTANTI_TD_3654_output_preprocess));
    trans_JOIN_LEFTANTI_TD_3654_out.add(&(tbl_JOIN_INNER_TD_0691_output));
    trans_JOIN_LEFTANTI_TD_3654_out.dev2host(0, &(events_JOIN_LEFTANTI_TD_3654), &(events_d2h_rd_JOIN_LEFTANTI_TD_3654[0]));
    q_h.flush();
    q_h.finish();
    SW_JOIN_LEFTANTI_TD_3654_concatenate(tbl_JOIN_LEFTANTI_TD_3654_output_preprocess, tbl_JOIN_INNER_TD_0691_output);
    tbl_JOIN_LEFTANTI_TD_3654_output_preprocess.copyTableData(&(tbl_JOIN_LEFTANTI_TD_3654_output));
    gettimeofday(&tv_r_JOIN_LEFTANTI_3_20_e, 0);

    struct timeval tv_r_Aggregate_2_911_s, tv_r_Aggregate_2_911_e;
    gettimeofday(&tv_r_Aggregate_2_911_s, 0);
    trans_Aggregate_TD_2946.add(&(tbl_JOIN_LEFTANTI_TD_3654_output));
    trans_Aggregate_TD_2946.host2dev(0, &(prev_events_grp_Aggregate_TD_2946), &(events_h2d_wr_Aggregate_TD_2946[0]));
    events_grp_Aggregate_TD_2946.push_back(events_h2d_wr_Aggregate_TD_2946[0]);
    krnl_Aggregate_TD_2946.run(0, &(events_grp_Aggregate_TD_2946), &(events_Aggregate_TD_2946[0]));
    
    trans_Aggregate_TD_2946_out.add(&(tbl_Aggregate_TD_2946_output_preprocess));
    trans_Aggregate_TD_2946_out.dev2host(0, &(events_Aggregate_TD_2946), &(events_d2h_rd_Aggregate_TD_2946[0]));
    q_a.flush();
    q_a.finish();
    
    SW_Aggregate_TD_2946_consolidate(tbl_Aggregate_TD_2946_output_preprocess, tbl_Aggregate_TD_2946_output);
    gettimeofday(&tv_r_Aggregate_2_911_e, 0);

    struct timeval tv_r_Aggregate_1_101_s, tv_r_Aggregate_1_101_e;
    gettimeofday(&tv_r_Aggregate_1_101_s, 0);
    prev_events_grp_Aggregate_TD_1609.push_back(events_h2d_wr_Aggregate_TD_2946[0]);
    trans_Aggregate_TD_1609.add(&(tbl_Aggregate_TD_2946_output));
    trans_Aggregate_TD_1609.host2dev(0, &(prev_events_grp_Aggregate_TD_1609), &(events_h2d_wr_Aggregate_TD_1609[0]));
    events_grp_Aggregate_TD_1609.push_back(events_h2d_wr_Aggregate_TD_1609[0]);
    events_grp_Aggregate_TD_1609.push_back(events_Aggregate_TD_2946[0]);
    krnl_Aggregate_TD_1609.run(0, &(events_grp_Aggregate_TD_1609), &(events_Aggregate_TD_1609[0]));
    
    trans_Aggregate_TD_1609_out.add(&(tbl_Aggregate_TD_1609_output_preprocess));
    trans_Aggregate_TD_1609_out.dev2host(0, &(events_Aggregate_TD_1609), &(events_d2h_rd_Aggregate_TD_1609[0]));
    q_a.flush();
    q_a.finish();
    
    SW_Aggregate_TD_1609_consolidate(tbl_Aggregate_TD_1609_output_preprocess, tbl_Aggregate_TD_1609_output);
    gettimeofday(&tv_r_Aggregate_1_101_e, 0);

    struct timeval tv_r_Sort_0_875_s, tv_r_Sort_0_875_e;
    gettimeofday(&tv_r_Sort_0_875_s, 0);

    // HW_Sort_TD_0263(tbl_Aggregate_TD_1609_output, tbl_Sort_TD_0263_output);
    // startExecution
    for (i = 0; i < TREE_COUNT; i++) {
        OCL_CHECK(err, err = q_a.enqueueMigrateMemObjects({buffer_0[i]},0/* 0 means from host*/));
    }
    OCL_CHECK(err, err = q_a.finish());
    std::cout << "Copy data from host to FPGA is done!" << std::endl;
    
    //Launch the Kernel
    OCL_CHECK(err, err = q_a.enqueueTask(krnl_sorter, NULL, &sortKrnlEvent));
    clWaitForEvents(1, (const cl_event*) &sortKrnlEvent);
    std::cout << "Kernel execution is done!" << std::endl;

    //Copy Result from Device Global Memory to Host Local Memory
    if (num_pass % 2 == 1)
    {
        for (i = 0; i < TREE_COUNT; i++) {
            OCL_CHECK(err, err = q_a.enqueueMigrateMemObjects({buffer_0[i]}, CL_MIGRATE_MEM_OBJECT_HOST));
        }
    }
    else
    {
        for (i = 0; i < TREE_COUNT; i++) {
            OCL_CHECK(err, err = q_a.enqueueMigrateMemObjects({buffer_1[i]}, CL_MIGRATE_MEM_OBJECT_HOST));
        }
    }
    OCL_CHECK(err, err = q_a.finish());
    std::cout << "Copy data from FPGA to host is done!" << std::endl;
    //SW_Sort_TD_0263(tbl_Aggregate_TD_1609_output, tbl_Sort_TD_0263_output);
    gettimeofday(&tv_r_Sort_0_875_e, 0);

    gettimeofday(&tv_r_e, 0); 
    // **************************** Print Execution Time ************************** // 
    std::cout << "Filter_4: " << tvdiff(&tv_r_Filter_4_323_s, &tv_r_Filter_4_323_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_59_input: " << tbl_SerializeFromObject_TD_59_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_0: " << tvdiff(&tv_r_JOIN_INNER_0_116_s, &tv_r_JOIN_INNER_0_116_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_4820_input: " << tbl_SerializeFromObject_TD_4820_input.getNumRow() << " " << "tbl_Filter_TD_470_output: " << tbl_Filter_TD_470_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_LEFTANTI_3: " << tvdiff(&tv_r_JOIN_LEFTANTI_3_20_s, &tv_r_JOIN_LEFTANTI_3_20_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_0691_output: " << tbl_JOIN_INNER_TD_0691_output.getNumRow() << " " << "tbl_SerializeFromObject_TD_4820_input: " << tbl_SerializeFromObject_TD_4820_input.getNumRow() << " " << std::endl; 

    std::cout << "Aggregate_2: " << tvdiff(&tv_r_Aggregate_2_911_s, &tv_r_Aggregate_2_911_e) / 1000.0 << " ms " 
     << "tbl_JOIN_LEFTANTI_TD_3654_output: " << tbl_JOIN_LEFTANTI_TD_3654_output.getNumRow() << " " << std::endl; 

    std::cout << "Aggregate_1: " << tvdiff(&tv_r_Aggregate_1_101_s, &tv_r_Aggregate_1_101_e) / 1000.0 << " ms " 
     << "tbl_Aggregate_TD_2946_output: " << tbl_Aggregate_TD_2946_output.getNumRow() << " " << std::endl; 

    std::cout << "Sort_0: " << tvdiff(&tv_r_Sort_0_875_s, &tv_r_Sort_0_875_e) / 1000.0 << " ms " 
     << "tbl_Aggregate_TD_1609_output: " << tbl_Aggregate_TD_1609_output.getNumRow() << " " << std::endl; 

    std::cout << std::endl << " Total execution time: " << tvdiff(&tv_r_s, &tv_r_e) / 1000 << " ms"; 

    std::cout << std::endl << " Spark elapsed time: " << 6.714391 * 1000 << "ms" << std::endl; 
    return 0; 
}
