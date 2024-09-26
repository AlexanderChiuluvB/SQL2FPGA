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
const int PU_NM = 8; 

#include "table_dt.hpp" 
#include "utils.hpp" 
#include "tpch_read_2.hpp" 
#include "gqe_api.hpp" 

#include "cfgFunc_q13.hpp" 
#include "q13.hpp" 

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
    int32_t orders_n = SF1_ORDERS; 
    int32_t customer_n = SF1_CUSTOMER; 
    int32_t region_n = SF1_REGION; 
    int32_t part_n = SF1_PART; 
    int32_t partsupp_n = SF1_PARTSUPP; 
    if (scale == 30) { 
        lineitem_n = SF30_LINEITEM; 
        supplier_n = SF30_SUPPLIER; 
        nation_n = SF30_NATION; 
        orders_n = SF30_ORDERS; 
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
    // ****************************** Tables **************************** // 
    Table tbl_Sort_TD_0342_output("tbl_Sort_TD_0342_output", 6100000, 2, "");
    tbl_Sort_TD_0342_output.allocateHost();
    Table tbl_Aggregate_TD_1527_output_preprocess("tbl_Aggregate_TD_1527_output_preprocess", -1, 16, "");
    tbl_Aggregate_TD_1527_output_preprocess.allocateHost();
    Table tbl_Aggregate_TD_1527_output("tbl_Aggregate_TD_1527_output", -1, 2, "");
    tbl_Aggregate_TD_1527_output.allocateHost();
    Table tbl_Aggregate_TD_2488_output_preprocess("tbl_Aggregate_TD_2488_output_preprocess", -1, 16, "");
    tbl_Aggregate_TD_2488_output_preprocess.allocateHost();
    Table tbl_Aggregate_TD_2488_output("tbl_Aggregate_TD_2488_output", -1, 1, "");
    tbl_Aggregate_TD_2488_output.allocateHost();
    Table tbl_JOIN_LEFTANTI_TD_3476_output_preprocess("tbl_JOIN_LEFTANTI_TD_3476_output_preprocess", 1531000, 2, "");
    tbl_JOIN_LEFTANTI_TD_3476_output_preprocess.allocateHost();
    Table tbl_JOIN_LEFTANTI_TD_3476_output("tbl_JOIN_LEFTANTI_TD_3476_output", 1531000, 2, "");
    tbl_JOIN_LEFTANTI_TD_3476_output.allocateHost();
    Table tbl_JOIN_INNER_TD_0561_output("tbl_JOIN_INNER_TD_0561_output", 1480133, 3, "");
    tbl_JOIN_INNER_TD_0561_output.allocateHost();
    Table tbl_SerializeFromObject_TD_4730_input;
    tbl_SerializeFromObject_TD_4730_input = Table("customer", customer_n, 1, in_dir);
    tbl_SerializeFromObject_TD_4730_input.addCol("c_custkey", 4);
    tbl_SerializeFromObject_TD_4730_input.allocateHost();
    tbl_SerializeFromObject_TD_4730_input.loadHost();
    Table tbl_Filter_TD_4206_output("tbl_Filter_TD_4206_output", 6100000, 2, "");
    tbl_Filter_TD_4206_output.allocateHost();
    Table tbl_SerializeFromObject_TD_5927_input;
    tbl_SerializeFromObject_TD_5927_input = Table("orders", orders_n, 3, in_dir);
    tbl_SerializeFromObject_TD_5927_input.addCol("o_orderkey", 4);
    tbl_SerializeFromObject_TD_5927_input.addCol("o_custkey", 4);
    tbl_SerializeFromObject_TD_5927_input.addCol("o_comment", TPCH_READ_O_CMNT_MAX+1);
    tbl_SerializeFromObject_TD_5927_input.allocateHost();
    tbl_SerializeFromObject_TD_5927_input.loadHost();
    // ********************** Allocate Device Buffer ******************** // 
    tbl_Aggregate_TD_1527_output_preprocess.allocateDevBuffer(context_a, 33);
    tbl_JOIN_LEFTANTI_TD_3476_output.allocateDevBuffer(context_a, 32);
    tbl_Aggregate_TD_2488_output_preprocess.allocateDevBuffer(context_a, 33);
    tbl_Aggregate_TD_2488_output.allocateDevBuffer(context_a, 32);
    tbl_JOIN_LEFTANTI_TD_3476_output_preprocess.allocateDevBuffer(context_h, 32);
    tbl_JOIN_INNER_TD_0561_output.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_4730_input.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_4206_output.allocateDevBuffer(context_h, 32);
    // ****************************** Config **************************** // 
    AggrCfgCmd cfg_Aggregate_TD_1527_cmds;
    cfg_Aggregate_TD_1527_cmds.allocateHost();
    get_cfg_dat_Aggregate_TD_1527_gqe_aggr(cfg_Aggregate_TD_1527_cmds.cmd);
    cfg_Aggregate_TD_1527_cmds.allocateDevBuffer(context_a, 32);
    AggrCfgCmd cfg_Aggregate_TD_1527_cmds_out;
    cfg_Aggregate_TD_1527_cmds_out.allocateHost();
    cfg_Aggregate_TD_1527_cmds_out.allocateDevBuffer(context_a, 33);
    AggrCfgCmd cfg_Aggregate_TD_2488_cmds;
    cfg_Aggregate_TD_2488_cmds.allocateHost();
    get_cfg_dat_Aggregate_TD_2488_gqe_aggr(cfg_Aggregate_TD_2488_cmds.cmd);
    cfg_Aggregate_TD_2488_cmds.allocateDevBuffer(context_a, 32);
    AggrCfgCmd cfg_Aggregate_TD_2488_cmds_out;
    cfg_Aggregate_TD_2488_cmds_out.allocateHost();
    cfg_Aggregate_TD_2488_cmds_out.allocateDevBuffer(context_a, 33);
    cfgCmd cfg_JOIN_LEFTANTI_TD_3476_cmds;
    cfg_JOIN_LEFTANTI_TD_3476_cmds.allocateHost();
    get_cfg_dat_JOIN_LEFTANTI_TD_3476_gqe_join (cfg_JOIN_LEFTANTI_TD_3476_cmds.cmd);
    cfg_JOIN_LEFTANTI_TD_3476_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_INNER_TD_0561_cmds;
    cfg_JOIN_INNER_TD_0561_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_0561_gqe_join (cfg_JOIN_INNER_TD_0561_cmds.cmd);
    cfg_JOIN_INNER_TD_0561_cmds.allocateDevBuffer(context_h, 32);
    // *************************** Kernel Setup ************************* // 
    bufferTmp buftmp_h(context_h); 
    buftmp_h.initBuffer(q_h); 
    AggrBufferTmp buftmp_a(context_a); 
    buftmp_a.BufferInitial(q_a); 
    std::cout << std::endl; 
    AggrKrnlEngine krnl_Aggregate_TD_1527;
    krnl_Aggregate_TD_1527 = AggrKrnlEngine(program_a, q_a, "gqeAggr");
    krnl_Aggregate_TD_1527.setup(tbl_Aggregate_TD_2488_output, tbl_Aggregate_TD_1527_output_preprocess, cfg_Aggregate_TD_1527_cmds, cfg_Aggregate_TD_1527_cmds_out, buftmp_a);
    AggrKrnlEngine krnl_Aggregate_TD_2488;
    krnl_Aggregate_TD_2488 = AggrKrnlEngine(program_a, q_a, "gqeAggr");
    krnl_Aggregate_TD_2488.setup(tbl_JOIN_LEFTANTI_TD_3476_output, tbl_Aggregate_TD_2488_output_preprocess, cfg_Aggregate_TD_2488_cmds, cfg_Aggregate_TD_2488_cmds_out, buftmp_a);
    krnlEngine krnl_JOIN_LEFTANTI_TD_3476;
    krnl_JOIN_LEFTANTI_TD_3476 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_LEFTANTI_TD_3476.setup(tbl_SerializeFromObject_TD_4730_input, tbl_JOIN_INNER_TD_0561_output, tbl_JOIN_LEFTANTI_TD_3476_output_preprocess, cfg_JOIN_LEFTANTI_TD_3476_cmds, buftmp_h);
    krnlEngine krnl_JOIN_INNER_TD_0561;
    krnl_JOIN_INNER_TD_0561 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_0561.setup(tbl_SerializeFromObject_TD_4730_input, tbl_Filter_TD_4206_output, tbl_JOIN_INNER_TD_0561_output, cfg_JOIN_INNER_TD_0561_cmds, buftmp_h);
    // ************************** Transfer Engine *********************** // 
    transEngine trans_Aggregate_TD_1527;
    trans_Aggregate_TD_1527.setq(q_a);
    trans_Aggregate_TD_1527.add(&(cfg_Aggregate_TD_1527_cmds));
    transEngine trans_Aggregate_TD_1527_out;
    trans_Aggregate_TD_1527_out.setq(q_a);
    q_a.finish();
    transEngine trans_Aggregate_TD_2488;
    trans_Aggregate_TD_2488.setq(q_a);
    trans_Aggregate_TD_2488.add(&(cfg_Aggregate_TD_2488_cmds));
    transEngine trans_Aggregate_TD_2488_out;
    trans_Aggregate_TD_2488_out.setq(q_a);
    q_a.finish();
    transEngine trans_JOIN_LEFTANTI_TD_3476;
    trans_JOIN_LEFTANTI_TD_3476.setq(q_h);
    trans_JOIN_LEFTANTI_TD_3476.add(&(cfg_JOIN_LEFTANTI_TD_3476_cmds));
    trans_JOIN_LEFTANTI_TD_3476.add(&(tbl_SerializeFromObject_TD_4730_input));
    transEngine trans_JOIN_LEFTANTI_TD_3476_out;
    trans_JOIN_LEFTANTI_TD_3476_out.setq(q_h);
    q_h.finish();
    transEngine trans_JOIN_INNER_TD_0561;
    trans_JOIN_INNER_TD_0561.setq(q_h);
    trans_JOIN_INNER_TD_0561.add(&(cfg_JOIN_INNER_TD_0561_cmds));
    trans_JOIN_INNER_TD_0561.add(&(tbl_SerializeFromObject_TD_4730_input));
    q_h.finish();
    // ****************************** Events **************************** // 
    std::vector<cl::Event> events_h2d_wr_Aggregate_TD_1527;
    std::vector<cl::Event> events_d2h_rd_Aggregate_TD_1527;
    std::vector<cl::Event> events_Aggregate_TD_1527;
    events_h2d_wr_Aggregate_TD_1527.resize(1);
    events_d2h_rd_Aggregate_TD_1527.resize(1);
    events_Aggregate_TD_1527.resize(1);
    std::vector<cl::Event> events_grp_Aggregate_TD_1527;
    std::vector<cl::Event> prev_events_grp_Aggregate_TD_1527;
    std::vector<cl::Event> events_h2d_wr_Aggregate_TD_2488;
    std::vector<cl::Event> events_d2h_rd_Aggregate_TD_2488;
    std::vector<cl::Event> events_Aggregate_TD_2488;
    events_h2d_wr_Aggregate_TD_2488.resize(1);
    events_d2h_rd_Aggregate_TD_2488.resize(1);
    events_Aggregate_TD_2488.resize(1);
    std::vector<cl::Event> events_grp_Aggregate_TD_2488;
    std::vector<cl::Event> prev_events_grp_Aggregate_TD_2488;
    std::vector<cl::Event> events_h2d_wr_JOIN_LEFTANTI_TD_3476;
    std::vector<cl::Event> events_d2h_rd_JOIN_LEFTANTI_TD_3476;
    std::vector<cl::Event> events_JOIN_LEFTANTI_TD_3476;
    events_h2d_wr_JOIN_LEFTANTI_TD_3476.resize(1);
    events_d2h_rd_JOIN_LEFTANTI_TD_3476.resize(1);
    events_JOIN_LEFTANTI_TD_3476.resize(1);
    std::vector<cl::Event> events_grp_JOIN_LEFTANTI_TD_3476;
    std::vector<cl::Event> prev_events_grp_JOIN_LEFTANTI_TD_3476;
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_0561;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_0561;
    std::vector<cl::Event> events_JOIN_INNER_TD_0561;
    events_h2d_wr_JOIN_INNER_TD_0561.resize(1);
    events_d2h_rd_JOIN_INNER_TD_0561.resize(1);
    events_JOIN_INNER_TD_0561.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_0561;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_0561;
    // **************************** Operations ************************** // 
    struct timeval tv_r_s, tv_r_e; 
    gettimeofday(&tv_r_s, 0); 

    struct timeval tv_r_Filter_4_863_s, tv_r_Filter_4_863_e;
    gettimeofday(&tv_r_Filter_4_863_s, 0);
    SW_Filter_TD_4206(tbl_SerializeFromObject_TD_5927_input, tbl_Filter_TD_4206_output);
    gettimeofday(&tv_r_Filter_4_863_e, 0);

    struct timeval tv_r_JOIN_INNER_0_834_s, tv_r_JOIN_INNER_0_834_e;
    gettimeofday(&tv_r_JOIN_INNER_0_834_s, 0);
    trans_JOIN_INNER_TD_0561.add(&(tbl_Filter_TD_4206_output));
    trans_JOIN_INNER_TD_0561.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_0561), &(events_h2d_wr_JOIN_INNER_TD_0561[0]));
    events_grp_JOIN_INNER_TD_0561.push_back(events_h2d_wr_JOIN_INNER_TD_0561[0]);
    krnl_JOIN_INNER_TD_0561.run(0, &(events_grp_JOIN_INNER_TD_0561), &(events_JOIN_INNER_TD_0561[0]));
    gettimeofday(&tv_r_JOIN_INNER_0_834_e, 0);

    struct timeval tv_r_JOIN_LEFTANTI_3_829_s, tv_r_JOIN_LEFTANTI_3_829_e;
    gettimeofday(&tv_r_JOIN_LEFTANTI_3_829_s, 0);
    prev_events_grp_JOIN_LEFTANTI_TD_3476.push_back(events_h2d_wr_JOIN_INNER_TD_0561[0]);
    trans_JOIN_LEFTANTI_TD_3476.host2dev(0, &(prev_events_grp_JOIN_LEFTANTI_TD_3476), &(events_h2d_wr_JOIN_LEFTANTI_TD_3476[0]));
    events_grp_JOIN_LEFTANTI_TD_3476.push_back(events_h2d_wr_JOIN_LEFTANTI_TD_3476[0]);
    events_grp_JOIN_LEFTANTI_TD_3476.push_back(events_JOIN_INNER_TD_0561[0]);
    krnl_JOIN_LEFTANTI_TD_3476.run(0, &(events_grp_JOIN_LEFTANTI_TD_3476), &(events_JOIN_LEFTANTI_TD_3476[0]));
    
    trans_JOIN_LEFTANTI_TD_3476_out.add(&(tbl_JOIN_LEFTANTI_TD_3476_output_preprocess));
    trans_JOIN_LEFTANTI_TD_3476_out.add(&(tbl_JOIN_INNER_TD_0561_output));
    trans_JOIN_LEFTANTI_TD_3476_out.dev2host(0, &(events_JOIN_LEFTANTI_TD_3476), &(events_d2h_rd_JOIN_LEFTANTI_TD_3476[0]));
    q_h.flush();
    q_h.finish();
    SW_JOIN_LEFTANTI_TD_3476_concatenate(tbl_JOIN_LEFTANTI_TD_3476_output_preprocess, tbl_JOIN_INNER_TD_0561_output);
    tbl_JOIN_LEFTANTI_TD_3476_output_preprocess.copyTableData(&(tbl_JOIN_LEFTANTI_TD_3476_output));
    gettimeofday(&tv_r_JOIN_LEFTANTI_3_829_e, 0);

    struct timeval tv_r_Aggregate_2_668_s, tv_r_Aggregate_2_668_e;
    gettimeofday(&tv_r_Aggregate_2_668_s, 0);
    trans_Aggregate_TD_2488.add(&(tbl_JOIN_LEFTANTI_TD_3476_output));
    trans_Aggregate_TD_2488.host2dev(0, &(prev_events_grp_Aggregate_TD_2488), &(events_h2d_wr_Aggregate_TD_2488[0]));
    events_grp_Aggregate_TD_2488.push_back(events_h2d_wr_Aggregate_TD_2488[0]);
    krnl_Aggregate_TD_2488.run(0, &(events_grp_Aggregate_TD_2488), &(events_Aggregate_TD_2488[0]));
    
    trans_Aggregate_TD_2488_out.add(&(tbl_Aggregate_TD_2488_output_preprocess));
    trans_Aggregate_TD_2488_out.dev2host(0, &(events_Aggregate_TD_2488), &(events_d2h_rd_Aggregate_TD_2488[0]));
    q_a.flush();
    q_a.finish();
    
    SW_Aggregate_TD_2488_consolidate(tbl_Aggregate_TD_2488_output_preprocess, tbl_Aggregate_TD_2488_output);
    gettimeofday(&tv_r_Aggregate_2_668_e, 0);

    struct timeval tv_r_Aggregate_1_903_s, tv_r_Aggregate_1_903_e;
    gettimeofday(&tv_r_Aggregate_1_903_s, 0);
    prev_events_grp_Aggregate_TD_1527.push_back(events_h2d_wr_Aggregate_TD_2488[0]);
    trans_Aggregate_TD_1527.add(&(tbl_Aggregate_TD_2488_output));
    trans_Aggregate_TD_1527.host2dev(0, &(prev_events_grp_Aggregate_TD_1527), &(events_h2d_wr_Aggregate_TD_1527[0]));
    events_grp_Aggregate_TD_1527.push_back(events_h2d_wr_Aggregate_TD_1527[0]);
    events_grp_Aggregate_TD_1527.push_back(events_Aggregate_TD_2488[0]);
    krnl_Aggregate_TD_1527.run(0, &(events_grp_Aggregate_TD_1527), &(events_Aggregate_TD_1527[0]));
    
    trans_Aggregate_TD_1527_out.add(&(tbl_Aggregate_TD_1527_output_preprocess));
    trans_Aggregate_TD_1527_out.dev2host(0, &(events_Aggregate_TD_1527), &(events_d2h_rd_Aggregate_TD_1527[0]));
    q_a.flush();
    q_a.finish();
    
    SW_Aggregate_TD_1527_consolidate(tbl_Aggregate_TD_1527_output_preprocess, tbl_Aggregate_TD_1527_output);
    gettimeofday(&tv_r_Aggregate_1_903_e, 0);

    struct timeval tv_r_Sort_0_934_s, tv_r_Sort_0_934_e;
    gettimeofday(&tv_r_Sort_0_934_s, 0);
    SW_Sort_TD_0342(tbl_Aggregate_TD_1527_output, tbl_Sort_TD_0342_output);
    gettimeofday(&tv_r_Sort_0_934_e, 0);

    gettimeofday(&tv_r_e, 0); 
    // **************************** Print Execution Time ************************** // 
    std::cout << "Filter_4: " << tvdiff(&tv_r_Filter_4_863_s, &tv_r_Filter_4_863_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_5927_input: " << tbl_SerializeFromObject_TD_5927_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_0: " << tvdiff(&tv_r_JOIN_INNER_0_834_s, &tv_r_JOIN_INNER_0_834_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_4730_input: " << tbl_SerializeFromObject_TD_4730_input.getNumRow() << " " << "tbl_Filter_TD_4206_output: " << tbl_Filter_TD_4206_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_LEFTANTI_3: " << tvdiff(&tv_r_JOIN_LEFTANTI_3_829_s, &tv_r_JOIN_LEFTANTI_3_829_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_0561_output: " << tbl_JOIN_INNER_TD_0561_output.getNumRow() << " " << "tbl_SerializeFromObject_TD_4730_input: " << tbl_SerializeFromObject_TD_4730_input.getNumRow() << " " << std::endl; 

    std::cout << "Aggregate_2: " << tvdiff(&tv_r_Aggregate_2_668_s, &tv_r_Aggregate_2_668_e) / 1000.0 << " ms " 
     << "tbl_JOIN_LEFTANTI_TD_3476_output: " << tbl_JOIN_LEFTANTI_TD_3476_output.getNumRow() << " " << std::endl; 

    std::cout << "Aggregate_1: " << tvdiff(&tv_r_Aggregate_1_903_s, &tv_r_Aggregate_1_903_e) / 1000.0 << " ms " 
     << "tbl_Aggregate_TD_2488_output: " << tbl_Aggregate_TD_2488_output.getNumRow() << " " << std::endl; 

    std::cout << "Sort_0: " << tvdiff(&tv_r_Sort_0_934_s, &tv_r_Sort_0_934_e) / 1000.0 << " ms " 
     << "tbl_Aggregate_TD_1527_output: " << tbl_Aggregate_TD_1527_output.getNumRow() << " " << std::endl; 

    std::cout << std::endl << " Total execution time: " << tvdiff(&tv_r_s, &tv_r_e) / 1000 << " ms"; 

    std::cout << std::endl << " Spark elapsed time: " << 13.6997 * 1000 << "ms" << std::endl; 
    return 0; 
}
