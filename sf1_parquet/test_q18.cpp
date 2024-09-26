// number of overlays (w/o fusion): 6 
// number of overlays (w/ fusion): 6 
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

#include "cfgFunc_q18.hpp" 
#include "q18.hpp" 

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
    std::cout << "NOTE:running query #18\n."; 
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
    Table tbl_Sort_TD_0923_output("tbl_Sort_TD_0923_output", 6100000, 6, "");
    tbl_Sort_TD_0923_output.allocateHost();
    Table tbl_Aggregate_TD_1120_output("tbl_Aggregate_TD_1120_output", 6100000, 6, "");
    tbl_Aggregate_TD_1120_output.allocateHost();
    Table tbl_JOIN_INNER_TD_2768_output("tbl_JOIN_INNER_TD_2768_output", 100, 6, "");
    tbl_JOIN_INNER_TD_2768_output.allocateHost();
    Table tbl_JOIN_INNER_TD_3130_output("tbl_JOIN_INNER_TD_3130_output", 100, 5, "");
    tbl_JOIN_INNER_TD_3130_output.allocateHost();
    Table tbl_JOIN_LEFTSEMI_TD_354_output("tbl_JOIN_LEFTSEMI_TD_354_output", 100, 2, "");
    tbl_JOIN_LEFTSEMI_TD_354_output.allocateHost();
    Table tbl_SerializeFromObject_TD_4803_input_stringRowIDSubstitute;
    tbl_SerializeFromObject_TD_4803_input_stringRowIDSubstitute = Table("customer", customer_n, 2, in_dir);
    tbl_SerializeFromObject_TD_4803_input_stringRowIDSubstitute.addCol("c_custkey", 4);
    tbl_SerializeFromObject_TD_4803_input_stringRowIDSubstitute.addCol("c_name", 4, 1, 0);
    tbl_SerializeFromObject_TD_4803_input_stringRowIDSubstitute.allocateHost();
    tbl_SerializeFromObject_TD_4803_input_stringRowIDSubstitute.loadHost();
    Table tbl_SerializeFromObject_TD_4803_input;
    tbl_SerializeFromObject_TD_4803_input = Table("customer", customer_n, 2, in_dir);
    tbl_SerializeFromObject_TD_4803_input.addCol("c_custkey", 4);
    tbl_SerializeFromObject_TD_4803_input.addCol("c_name", TPCH_READ_C_NAME_LEN+1);
    tbl_SerializeFromObject_TD_4803_input.allocateHost();
    tbl_SerializeFromObject_TD_4803_input.loadHost();
    Table tbl_JOIN_LEFTSEMI_TD_4363_output("tbl_JOIN_LEFTSEMI_TD_4363_output", 100, 4, "");
    tbl_JOIN_LEFTSEMI_TD_4363_output.allocateHost();
    Table tbl_SerializeFromObject_TD_4263_input;
    tbl_SerializeFromObject_TD_4263_input = Table("lineitem", lineitem_n, 2, in_dir);
    tbl_SerializeFromObject_TD_4263_input.addCol("l_orderkey", 4);
    tbl_SerializeFromObject_TD_4263_input.addCol("l_quantity", 4);
    tbl_SerializeFromObject_TD_4263_input.allocateHost();
    tbl_SerializeFromObject_TD_4263_input.loadHost();
    Table tbl_Filter_TD_4736_output("tbl_Filter_TD_4736_output", 6100000, 1, "");
    tbl_Filter_TD_4736_output.allocateHost();
    Table tbl_SerializeFromObject_TD_5204_input;
    tbl_SerializeFromObject_TD_5204_input = Table("orders", orders_n, 4, in_dir);
    tbl_SerializeFromObject_TD_5204_input.addCol("o_orderkey", 4);
    tbl_SerializeFromObject_TD_5204_input.addCol("o_custkey", 4);
    tbl_SerializeFromObject_TD_5204_input.addCol("o_totalprice", 4);
    tbl_SerializeFromObject_TD_5204_input.addCol("o_orderdate", 4);
    tbl_SerializeFromObject_TD_5204_input.allocateHost();
    tbl_SerializeFromObject_TD_5204_input.loadHost();
    Table tbl_Filter_TD_54_output("tbl_Filter_TD_54_output", 6100000, 1, "");
    tbl_Filter_TD_54_output.allocateHost();
    Table tbl_Aggregate_TD_6111_output_preprocess("tbl_Aggregate_TD_6111_output_preprocess", 3000000, 16, "");
    tbl_Aggregate_TD_6111_output_preprocess.allocateHost();
    Table tbl_Aggregate_TD_6111_output("tbl_Aggregate_TD_6111_output", 3000000, 2, "");
    tbl_Aggregate_TD_6111_output.allocateHost();
    Table tbl_SerializeFromObject_TD_737_input;
    tbl_SerializeFromObject_TD_737_input = Table("lineitem", lineitem_n, 2, in_dir);
    tbl_SerializeFromObject_TD_737_input.addCol("l_orderkey", 4);
    tbl_SerializeFromObject_TD_737_input.addCol("l_quantity", 4);
    tbl_SerializeFromObject_TD_737_input.allocateHost();
    tbl_SerializeFromObject_TD_737_input.loadHost();
    // ********************** Allocate Device Buffer ******************** // 
    tbl_JOIN_INNER_TD_2768_output.allocateDevBuffer(context_h, 32);
    tbl_JOIN_INNER_TD_3130_output.allocateDevBuffer(context_h, 32);
    tbl_JOIN_LEFTSEMI_TD_354_output.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_4803_input_stringRowIDSubstitute.allocateDevBuffer(context_h, 32);
    tbl_JOIN_LEFTSEMI_TD_4363_output.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_4263_input.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_4736_output.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_5204_input.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_54_output.allocateDevBuffer(context_h, 32);
    tbl_Aggregate_TD_6111_output_preprocess.allocateDevBuffer(context_a, 33);
    tbl_SerializeFromObject_TD_737_input.allocateDevBuffer(context_a, 32);
    // ****************************** Config **************************** // 
    cfgCmd cfg_JOIN_INNER_TD_2768_cmds;
    cfg_JOIN_INNER_TD_2768_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_2768_gqe_join (cfg_JOIN_INNER_TD_2768_cmds.cmd);
    cfg_JOIN_INNER_TD_2768_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_INNER_TD_3130_cmds;
    cfg_JOIN_INNER_TD_3130_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_3130_gqe_join (cfg_JOIN_INNER_TD_3130_cmds.cmd);
    cfg_JOIN_INNER_TD_3130_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_LEFTSEMI_TD_354_cmds;
    cfg_JOIN_LEFTSEMI_TD_354_cmds.allocateHost();
    get_cfg_dat_JOIN_LEFTSEMI_TD_354_gqe_join (cfg_JOIN_LEFTSEMI_TD_354_cmds.cmd);
    cfg_JOIN_LEFTSEMI_TD_354_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_LEFTSEMI_TD_4363_cmds;
    cfg_JOIN_LEFTSEMI_TD_4363_cmds.allocateHost();
    get_cfg_dat_JOIN_LEFTSEMI_TD_4363_gqe_join (cfg_JOIN_LEFTSEMI_TD_4363_cmds.cmd);
    cfg_JOIN_LEFTSEMI_TD_4363_cmds.allocateDevBuffer(context_h, 32);
    AggrCfgCmd cfg_Aggregate_TD_6111_cmds;
    cfg_Aggregate_TD_6111_cmds.allocateHost();
    get_cfg_dat_Aggregate_TD_6111_gqe_aggr(cfg_Aggregate_TD_6111_cmds.cmd);
    cfg_Aggregate_TD_6111_cmds.allocateDevBuffer(context_a, 32);
    AggrCfgCmd cfg_Aggregate_TD_6111_cmds_out;
    cfg_Aggregate_TD_6111_cmds_out.allocateHost();
    cfg_Aggregate_TD_6111_cmds_out.allocateDevBuffer(context_a, 33);
    // *************************** Kernel Setup ************************* // 
    bufferTmp buftmp_h(context_h); 
    buftmp_h.initBuffer(q_h); 
    AggrBufferTmp buftmp_a(context_a); 
    buftmp_a.BufferInitial(q_a); 
    std::cout << std::endl; 
    krnlEngine krnl_JOIN_INNER_TD_2768;
    krnl_JOIN_INNER_TD_2768 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_2768.setup(tbl_JOIN_INNER_TD_3130_output, tbl_JOIN_LEFTSEMI_TD_354_output, tbl_JOIN_INNER_TD_2768_output, cfg_JOIN_INNER_TD_2768_cmds, buftmp_h);
    krnlEngine krnl_JOIN_INNER_TD_3130;
    krnl_JOIN_INNER_TD_3130 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_3130.setup(tbl_SerializeFromObject_TD_4803_input_stringRowIDSubstitute, tbl_JOIN_LEFTSEMI_TD_4363_output, tbl_JOIN_INNER_TD_3130_output, cfg_JOIN_INNER_TD_3130_cmds, buftmp_h);
    krnlEngine krnl_JOIN_LEFTSEMI_TD_354;
    krnl_JOIN_LEFTSEMI_TD_354 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_LEFTSEMI_TD_354.setup(tbl_Filter_TD_4736_output, tbl_SerializeFromObject_TD_4263_input, tbl_JOIN_LEFTSEMI_TD_354_output, cfg_JOIN_LEFTSEMI_TD_354_cmds, buftmp_h);
    krnlEngine krnl_JOIN_LEFTSEMI_TD_4363;
    krnl_JOIN_LEFTSEMI_TD_4363 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_LEFTSEMI_TD_4363.setup(tbl_Filter_TD_54_output, tbl_SerializeFromObject_TD_5204_input, tbl_JOIN_LEFTSEMI_TD_4363_output, cfg_JOIN_LEFTSEMI_TD_4363_cmds, buftmp_h);
    AggrKrnlEngine krnl_Aggregate_TD_6111;
    krnl_Aggregate_TD_6111 = AggrKrnlEngine(program_a, q_a, "gqeAggr");
    krnl_Aggregate_TD_6111.setup(tbl_SerializeFromObject_TD_737_input, tbl_Aggregate_TD_6111_output_preprocess, cfg_Aggregate_TD_6111_cmds, cfg_Aggregate_TD_6111_cmds_out, buftmp_a);
    // ************************** Transfer Engine *********************** // 
    transEngine trans_JOIN_INNER_TD_2768;
    trans_JOIN_INNER_TD_2768.setq(q_h);
    trans_JOIN_INNER_TD_2768.add(&(cfg_JOIN_INNER_TD_2768_cmds));
    transEngine trans_JOIN_INNER_TD_2768_out;
    trans_JOIN_INNER_TD_2768_out.setq(q_h);
    q_h.finish();
    transEngine trans_JOIN_INNER_TD_3130;
    trans_JOIN_INNER_TD_3130.setq(q_h);
    trans_JOIN_INNER_TD_3130.add(&(cfg_JOIN_INNER_TD_3130_cmds));
    trans_JOIN_INNER_TD_3130.add(&(tbl_SerializeFromObject_TD_4803_input_stringRowIDSubstitute));
    q_h.finish();
    transEngine trans_JOIN_LEFTSEMI_TD_354;
    trans_JOIN_LEFTSEMI_TD_354.setq(q_h);
    trans_JOIN_LEFTSEMI_TD_354.add(&(cfg_JOIN_LEFTSEMI_TD_354_cmds));
    trans_JOIN_LEFTSEMI_TD_354.add(&(tbl_SerializeFromObject_TD_4263_input));
    q_h.finish();
    transEngine trans_JOIN_LEFTSEMI_TD_4363;
    trans_JOIN_LEFTSEMI_TD_4363.setq(q_h);
    trans_JOIN_LEFTSEMI_TD_4363.add(&(cfg_JOIN_LEFTSEMI_TD_4363_cmds));
    trans_JOIN_LEFTSEMI_TD_4363.add(&(tbl_SerializeFromObject_TD_5204_input));
    q_h.finish();
    transEngine trans_Aggregate_TD_6111;
    trans_Aggregate_TD_6111.setq(q_a);
    trans_Aggregate_TD_6111.add(&(cfg_Aggregate_TD_6111_cmds));
    trans_Aggregate_TD_6111.add(&(tbl_SerializeFromObject_TD_737_input));
    transEngine trans_Aggregate_TD_6111_out;
    trans_Aggregate_TD_6111_out.setq(q_a);
    q_a.finish();
    // ****************************** Events **************************** // 
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_2768;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_2768;
    std::vector<cl::Event> events_JOIN_INNER_TD_2768;
    events_h2d_wr_JOIN_INNER_TD_2768.resize(1);
    events_d2h_rd_JOIN_INNER_TD_2768.resize(1);
    events_JOIN_INNER_TD_2768.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_2768;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_2768;
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_3130;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_3130;
    std::vector<cl::Event> events_JOIN_INNER_TD_3130;
    events_h2d_wr_JOIN_INNER_TD_3130.resize(1);
    events_d2h_rd_JOIN_INNER_TD_3130.resize(1);
    events_JOIN_INNER_TD_3130.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_3130;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_3130;
    std::vector<cl::Event> events_h2d_wr_JOIN_LEFTSEMI_TD_354;
    std::vector<cl::Event> events_d2h_rd_JOIN_LEFTSEMI_TD_354;
    std::vector<cl::Event> events_JOIN_LEFTSEMI_TD_354;
    events_h2d_wr_JOIN_LEFTSEMI_TD_354.resize(1);
    events_d2h_rd_JOIN_LEFTSEMI_TD_354.resize(1);
    events_JOIN_LEFTSEMI_TD_354.resize(1);
    std::vector<cl::Event> events_grp_JOIN_LEFTSEMI_TD_354;
    std::vector<cl::Event> prev_events_grp_JOIN_LEFTSEMI_TD_354;
    std::vector<cl::Event> events_h2d_wr_JOIN_LEFTSEMI_TD_4363;
    std::vector<cl::Event> events_d2h_rd_JOIN_LEFTSEMI_TD_4363;
    std::vector<cl::Event> events_JOIN_LEFTSEMI_TD_4363;
    events_h2d_wr_JOIN_LEFTSEMI_TD_4363.resize(1);
    events_d2h_rd_JOIN_LEFTSEMI_TD_4363.resize(1);
    events_JOIN_LEFTSEMI_TD_4363.resize(1);
    std::vector<cl::Event> events_grp_JOIN_LEFTSEMI_TD_4363;
    std::vector<cl::Event> prev_events_grp_JOIN_LEFTSEMI_TD_4363;
    std::vector<cl::Event> events_h2d_wr_Aggregate_TD_6111;
    std::vector<cl::Event> events_d2h_rd_Aggregate_TD_6111;
    std::vector<cl::Event> events_Aggregate_TD_6111;
    events_h2d_wr_Aggregate_TD_6111.resize(1);
    events_d2h_rd_Aggregate_TD_6111.resize(1);
    events_Aggregate_TD_6111.resize(1);
    std::vector<cl::Event> events_grp_Aggregate_TD_6111;
    std::vector<cl::Event> prev_events_grp_Aggregate_TD_6111;
    // **************************** Operations ************************** // 
    struct timeval tv_r_s, tv_r_e; 
    gettimeofday(&tv_r_s, 0); 

    struct timeval tv_r_Aggregate_6_620_s, tv_r_Aggregate_6_620_e;
    gettimeofday(&tv_r_Aggregate_6_620_s, 0);
    trans_Aggregate_TD_6111.host2dev(0, &(prev_events_grp_Aggregate_TD_6111), &(events_h2d_wr_Aggregate_TD_6111[0]));
    events_grp_Aggregate_TD_6111.push_back(events_h2d_wr_Aggregate_TD_6111[0]);
    krnl_Aggregate_TD_6111.run(0, &(events_grp_Aggregate_TD_6111), &(events_Aggregate_TD_6111[0]));
    
    trans_Aggregate_TD_6111_out.add(&(tbl_Aggregate_TD_6111_output_preprocess));
    trans_Aggregate_TD_6111_out.dev2host(0, &(events_Aggregate_TD_6111), &(events_d2h_rd_Aggregate_TD_6111[0]));
    q_a.flush();
    q_a.finish();
    
    SW_Aggregate_TD_6111_consolidate(tbl_Aggregate_TD_6111_output_preprocess, tbl_Aggregate_TD_6111_output);
    gettimeofday(&tv_r_Aggregate_6_620_e, 0);

    struct timeval tv_r_Filter_5_408_s, tv_r_Filter_5_408_e;
    gettimeofday(&tv_r_Filter_5_408_s, 0);
    SW_Filter_TD_54(tbl_Aggregate_TD_6111_output, tbl_Filter_TD_54_output);
    gettimeofday(&tv_r_Filter_5_408_e, 0);

    struct timeval tv_r_Filter_4_796_s, tv_r_Filter_4_796_e;
    gettimeofday(&tv_r_Filter_4_796_s, 0);
    SW_Filter_TD_4736(tbl_Aggregate_TD_6111_output, tbl_Filter_TD_4736_output);
    gettimeofday(&tv_r_Filter_4_796_e, 0);

    struct timeval tv_r_JOIN_LEFTSEMI_4_457_s, tv_r_JOIN_LEFTSEMI_4_457_e;
    gettimeofday(&tv_r_JOIN_LEFTSEMI_4_457_s, 0);
    trans_JOIN_LEFTSEMI_TD_4363.add(&(tbl_Filter_TD_54_output));
    trans_JOIN_LEFTSEMI_TD_4363.host2dev(0, &(prev_events_grp_JOIN_LEFTSEMI_TD_4363), &(events_h2d_wr_JOIN_LEFTSEMI_TD_4363[0]));
    events_grp_JOIN_LEFTSEMI_TD_4363.push_back(events_h2d_wr_JOIN_LEFTSEMI_TD_4363[0]);
    krnl_JOIN_LEFTSEMI_TD_4363.run(0, &(events_grp_JOIN_LEFTSEMI_TD_4363), &(events_JOIN_LEFTSEMI_TD_4363[0]));
    gettimeofday(&tv_r_JOIN_LEFTSEMI_4_457_e, 0);

    struct timeval tv_r_JOIN_LEFTSEMI_3_510_s, tv_r_JOIN_LEFTSEMI_3_510_e;
    gettimeofday(&tv_r_JOIN_LEFTSEMI_3_510_s, 0);
    trans_JOIN_LEFTSEMI_TD_354.add(&(tbl_Filter_TD_4736_output));
    trans_JOIN_LEFTSEMI_TD_354.host2dev(0, &(prev_events_grp_JOIN_LEFTSEMI_TD_354), &(events_h2d_wr_JOIN_LEFTSEMI_TD_354[0]));
    events_grp_JOIN_LEFTSEMI_TD_354.push_back(events_h2d_wr_JOIN_LEFTSEMI_TD_354[0]);
    krnl_JOIN_LEFTSEMI_TD_354.run(0, &(events_grp_JOIN_LEFTSEMI_TD_354), &(events_JOIN_LEFTSEMI_TD_354[0]));
    gettimeofday(&tv_r_JOIN_LEFTSEMI_3_510_e, 0);

    struct timeval tv_r_JOIN_INNER_3_759_s, tv_r_JOIN_INNER_3_759_e;
    gettimeofday(&tv_r_JOIN_INNER_3_759_s, 0);
    prev_events_grp_JOIN_INNER_TD_3130.push_back(events_h2d_wr_JOIN_LEFTSEMI_TD_4363[0]);
    trans_JOIN_INNER_TD_3130.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_3130), &(events_h2d_wr_JOIN_INNER_TD_3130[0]));
    events_grp_JOIN_INNER_TD_3130.push_back(events_h2d_wr_JOIN_INNER_TD_3130[0]);
    events_grp_JOIN_INNER_TD_3130.push_back(events_JOIN_LEFTSEMI_TD_4363[0]);
    krnl_JOIN_INNER_TD_3130.run(0, &(events_grp_JOIN_INNER_TD_3130), &(events_JOIN_INNER_TD_3130[0]));
    gettimeofday(&tv_r_JOIN_INNER_3_759_e, 0);

    struct timeval tv_r_JOIN_INNER_2_886_s, tv_r_JOIN_INNER_2_886_e;
    gettimeofday(&tv_r_JOIN_INNER_2_886_s, 0);
    prev_events_grp_JOIN_INNER_TD_2768.push_back(events_h2d_wr_JOIN_INNER_TD_3130[0]);
    prev_events_grp_JOIN_INNER_TD_2768.push_back(events_h2d_wr_JOIN_LEFTSEMI_TD_354[0]);
    trans_JOIN_INNER_TD_2768.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_2768), &(events_h2d_wr_JOIN_INNER_TD_2768[0]));
    events_grp_JOIN_INNER_TD_2768.push_back(events_h2d_wr_JOIN_INNER_TD_2768[0]);
    events_grp_JOIN_INNER_TD_2768.push_back(events_JOIN_INNER_TD_3130[0]);
    events_grp_JOIN_INNER_TD_2768.push_back(events_JOIN_LEFTSEMI_TD_354[0]);
    krnl_JOIN_INNER_TD_2768.run(0, &(events_grp_JOIN_INNER_TD_2768), &(events_JOIN_INNER_TD_2768[0]));
    
    trans_JOIN_INNER_TD_2768_out.add(&(tbl_JOIN_INNER_TD_2768_output));
    trans_JOIN_INNER_TD_2768_out.dev2host(0, &(events_JOIN_INNER_TD_2768), &(events_d2h_rd_JOIN_INNER_TD_2768[0]));
    q_h.flush();
    q_h.finish();
    gettimeofday(&tv_r_JOIN_INNER_2_886_e, 0);

    struct timeval tv_r_Aggregate_1_883_s, tv_r_Aggregate_1_883_e;
    gettimeofday(&tv_r_Aggregate_1_883_s, 0);
    SW_Aggregate_TD_1120(tbl_JOIN_INNER_TD_2768_output, tbl_SerializeFromObject_TD_4803_input, tbl_Aggregate_TD_1120_output);
    gettimeofday(&tv_r_Aggregate_1_883_e, 0);

    struct timeval tv_r_Sort_0_211_s, tv_r_Sort_0_211_e;
    gettimeofday(&tv_r_Sort_0_211_s, 0);
    SW_Sort_TD_0923(tbl_Aggregate_TD_1120_output, tbl_Sort_TD_0923_output);
    gettimeofday(&tv_r_Sort_0_211_e, 0);

    gettimeofday(&tv_r_e, 0); 
    // **************************** Print Execution Time ************************** // 
    std::cout << "Aggregate_6: " << tvdiff(&tv_r_Aggregate_6_620_s, &tv_r_Aggregate_6_620_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_737_input: " << tbl_SerializeFromObject_TD_737_input.getNumRow() << " " << std::endl; 

    std::cout << "Filter_5: " << tvdiff(&tv_r_Filter_5_408_s, &tv_r_Filter_5_408_e) / 1000.0 << " ms " 
     << "tbl_Aggregate_TD_6111_output: " << tbl_Aggregate_TD_6111_output.getNumRow() << " " << std::endl; 

    std::cout << "Filter_4: " << tvdiff(&tv_r_Filter_4_796_s, &tv_r_Filter_4_796_e) / 1000.0 << " ms " 
     << "tbl_Aggregate_TD_6111_output: " << tbl_Aggregate_TD_6111_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_LEFTSEMI_4: " << tvdiff(&tv_r_JOIN_LEFTSEMI_4_457_s, &tv_r_JOIN_LEFTSEMI_4_457_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_5204_input: " << tbl_SerializeFromObject_TD_5204_input.getNumRow() << " " << "tbl_Filter_TD_54_output: " << tbl_Filter_TD_54_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_LEFTSEMI_3: " << tvdiff(&tv_r_JOIN_LEFTSEMI_3_510_s, &tv_r_JOIN_LEFTSEMI_3_510_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_4263_input: " << tbl_SerializeFromObject_TD_4263_input.getNumRow() << " " << "tbl_Filter_TD_4736_output: " << tbl_Filter_TD_4736_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_3: " << tvdiff(&tv_r_JOIN_INNER_3_759_s, &tv_r_JOIN_INNER_3_759_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_4803_input_stringRowIDSubstitute: " << tbl_SerializeFromObject_TD_4803_input_stringRowIDSubstitute.getNumRow() << " " << "tbl_JOIN_LEFTSEMI_TD_4363_output: " << tbl_JOIN_LEFTSEMI_TD_4363_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_2: " << tvdiff(&tv_r_JOIN_INNER_2_886_s, &tv_r_JOIN_INNER_2_886_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_3130_output: " << tbl_JOIN_INNER_TD_3130_output.getNumRow() << " " << "tbl_JOIN_LEFTSEMI_TD_354_output: " << tbl_JOIN_LEFTSEMI_TD_354_output.getNumRow() << " " << std::endl; 

    std::cout << "Aggregate_1: " << tvdiff(&tv_r_Aggregate_1_883_s, &tv_r_Aggregate_1_883_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_2768_output: " << tbl_JOIN_INNER_TD_2768_output.getNumRow() << " " << std::endl; 

    std::cout << "Sort_0: " << tvdiff(&tv_r_Sort_0_211_s, &tv_r_Sort_0_211_e) / 1000.0 << " ms " 
     << "tbl_Aggregate_TD_1120_output: " << tbl_Aggregate_TD_1120_output.getNumRow() << " " << std::endl; 

    std::cout << std::endl << " Total execution time: " << tvdiff(&tv_r_s, &tv_r_e) / 1000 << " ms"; 

    std::cout << std::endl << " Spark elapsed time: " << 82.45103 * 1000 << "ms" << std::endl; 
    return 0; 
}
