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
    Table tbl_Sort_TD_0126_output("tbl_Sort_TD_0126_output", 6100000, 6, "");
    tbl_Sort_TD_0126_output.allocateHost();
    Table tbl_Aggregate_TD_1464_output("tbl_Aggregate_TD_1464_output", 6100000, 6, "");
    tbl_Aggregate_TD_1464_output.allocateHost();
    Table tbl_JOIN_INNER_TD_2611_output("tbl_JOIN_INNER_TD_2611_output", 100, 6, "");
    tbl_JOIN_INNER_TD_2611_output.allocateHost();
    Table tbl_JOIN_INNER_TD_3935_output("tbl_JOIN_INNER_TD_3935_output", 100, 5, "");
    tbl_JOIN_INNER_TD_3935_output.allocateHost();
    Table tbl_Project_TD_3477_output("tbl_Project_TD_3477_output", 6100000, 2, "");
    tbl_Project_TD_3477_output.allocateHost();
    Table tbl_Project_TD_4345_output("tbl_Project_TD_4345_output", 6100000, 2, "");
    tbl_Project_TD_4345_output.allocateHost();
    Table tbl_Project_TD_4104_output("tbl_Project_TD_4104_output", 6100000, 4, "");
    tbl_Project_TD_4104_output.allocateHost();
    Table tbl_JOIN_LEFTSEMI_TD_4655_output("tbl_JOIN_LEFTSEMI_TD_4655_output", 6100000, 2, "");
    tbl_JOIN_LEFTSEMI_TD_4655_output.allocateHost();
    Table tbl_SerializeFromObject_TD_666_input_stringRowIDSubstitute;
    tbl_SerializeFromObject_TD_666_input_stringRowIDSubstitute = Table("customer", customer_n, 2, in_dir);
    tbl_SerializeFromObject_TD_666_input_stringRowIDSubstitute.addCol("c_custkey", 4);
    tbl_SerializeFromObject_TD_666_input_stringRowIDSubstitute.addCol("c_name", 4, 1, 0);
    tbl_SerializeFromObject_TD_666_input_stringRowIDSubstitute.allocateHost();
    tbl_SerializeFromObject_TD_666_input_stringRowIDSubstitute.loadHost();
    Table tbl_SerializeFromObject_TD_666_input;
    tbl_SerializeFromObject_TD_666_input = Table("customer", customer_n, 2, in_dir);
    tbl_SerializeFromObject_TD_666_input.addCol("c_custkey", 4);
    tbl_SerializeFromObject_TD_666_input.addCol("c_name", TPCH_READ_C_NAME_LEN+1);
    tbl_SerializeFromObject_TD_666_input.allocateHost();
    tbl_SerializeFromObject_TD_666_input.loadHost();
    Table tbl_JOIN_LEFTSEMI_TD_5796_output("tbl_JOIN_LEFTSEMI_TD_5796_output", 6100000, 4, "");
    tbl_JOIN_LEFTSEMI_TD_5796_output.allocateHost();
    Table tbl_SerializeFromObject_TD_6621_input;
    tbl_SerializeFromObject_TD_6621_input = Table("lineitem", lineitem_n, 2, in_dir);
    tbl_SerializeFromObject_TD_6621_input.addCol("l_orderkey", 4);
    tbl_SerializeFromObject_TD_6621_input.addCol("l_quantity", 4);
    tbl_SerializeFromObject_TD_6621_input.allocateHost();
    tbl_SerializeFromObject_TD_6621_input.loadHost();
    Table tbl_SerializeFromObject_TD_7614_input;
    tbl_SerializeFromObject_TD_7614_input = Table("orders", orders_n, 4, in_dir);
    tbl_SerializeFromObject_TD_7614_input.addCol("o_orderkey", 4);
    tbl_SerializeFromObject_TD_7614_input.addCol("o_custkey", 4);
    tbl_SerializeFromObject_TD_7614_input.addCol("o_totalprice", 4);
    tbl_SerializeFromObject_TD_7614_input.addCol("o_orderdate", 4);
    tbl_SerializeFromObject_TD_7614_input.allocateHost();
    tbl_SerializeFromObject_TD_7614_input.loadHost();
    Table tbl_Filter_TD_6726_output("tbl_Filter_TD_6726_output", 6100000, 1, "");
    tbl_Filter_TD_6726_output.allocateHost();
    Table tbl_Aggregate_TD_7555_output_preprocess("tbl_Aggregate_TD_7555_output_preprocess", -1, 16, "");
    tbl_Aggregate_TD_7555_output_preprocess.allocateHost();
    Table tbl_Aggregate_TD_7555_output("tbl_Aggregate_TD_7555_output", -1, 2, "");
    tbl_Aggregate_TD_7555_output.allocateHost();
    Table tbl_Project_TD_8215_output("tbl_Project_TD_8215_output", 6100000, 2, "");
    tbl_Project_TD_8215_output.allocateHost();
    Table tbl_SerializeFromObject_TD_9452_input;
    tbl_SerializeFromObject_TD_9452_input = Table("lineitem", lineitem_n, 2, in_dir);
    tbl_SerializeFromObject_TD_9452_input.addCol("l_orderkey", 4);
    tbl_SerializeFromObject_TD_9452_input.addCol("l_quantity", 4);
    tbl_SerializeFromObject_TD_9452_input.allocateHost();
    tbl_SerializeFromObject_TD_9452_input.loadHost();
    // ********************** Allocate Device Buffer ******************** // 
    tbl_JOIN_INNER_TD_2611_output.allocateDevBuffer(context_h, 32);
    tbl_JOIN_INNER_TD_3935_output.allocateDevBuffer(context_h, 32);
    tbl_Project_TD_3477_output.allocateDevBuffer(context_h, 32);
    tbl_Project_TD_4345_output.allocateDevBuffer(context_h, 32);
    tbl_Project_TD_4104_output.allocateDevBuffer(context_h, 32);
    tbl_Aggregate_TD_7555_output_preprocess.allocateDevBuffer(context_a, 33);
    tbl_Project_TD_8215_output.allocateDevBuffer(context_a, 32);
    // ****************************** Config **************************** // 
    cfgCmd cfg_JOIN_INNER_TD_2611_cmds;
    cfg_JOIN_INNER_TD_2611_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_2611_gqe_join (cfg_JOIN_INNER_TD_2611_cmds.cmd);
    cfg_JOIN_INNER_TD_2611_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_INNER_TD_3935_cmds;
    cfg_JOIN_INNER_TD_3935_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_3935_gqe_join (cfg_JOIN_INNER_TD_3935_cmds.cmd);
    cfg_JOIN_INNER_TD_3935_cmds.allocateDevBuffer(context_h, 32);
    AggrCfgCmd cfg_Aggregate_TD_7555_cmds;
    cfg_Aggregate_TD_7555_cmds.allocateHost();
    get_cfg_dat_Aggregate_TD_7555_gqe_aggr(cfg_Aggregate_TD_7555_cmds.cmd);
    cfg_Aggregate_TD_7555_cmds.allocateDevBuffer(context_a, 32);
    AggrCfgCmd cfg_Aggregate_TD_7555_cmds_out;
    cfg_Aggregate_TD_7555_cmds_out.allocateHost();
    cfg_Aggregate_TD_7555_cmds_out.allocateDevBuffer(context_a, 33);
    // *************************** Kernel Setup ************************* // 
    bufferTmp buftmp_h(context_h); 
    buftmp_h.initBuffer(q_h); 
    AggrBufferTmp buftmp_a(context_a); 
    buftmp_a.BufferInitial(q_a); 
    std::cout << std::endl; 
    krnlEngine krnl_JOIN_INNER_TD_2611;
    krnl_JOIN_INNER_TD_2611 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_2611.setup(tbl_JOIN_INNER_TD_3935_output, tbl_Project_TD_3477_output, tbl_JOIN_INNER_TD_2611_output, cfg_JOIN_INNER_TD_2611_cmds, buftmp_h);
    krnlEngine krnl_JOIN_INNER_TD_3935;
    krnl_JOIN_INNER_TD_3935 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_3935.setup(tbl_Project_TD_4345_output, tbl_Project_TD_4104_output, tbl_JOIN_INNER_TD_3935_output, cfg_JOIN_INNER_TD_3935_cmds, buftmp_h);
    AggrKrnlEngine krnl_Aggregate_TD_7555;
    krnl_Aggregate_TD_7555 = AggrKrnlEngine(program_a, q_a, "gqeAggr");
    krnl_Aggregate_TD_7555.setup(tbl_Project_TD_8215_output, tbl_Aggregate_TD_7555_output_preprocess, cfg_Aggregate_TD_7555_cmds, cfg_Aggregate_TD_7555_cmds_out, buftmp_a);
    // ************************** Transfer Engine *********************** // 
    transEngine trans_JOIN_INNER_TD_2611;
    trans_JOIN_INNER_TD_2611.setq(q_h);
    trans_JOIN_INNER_TD_2611.add(&(cfg_JOIN_INNER_TD_2611_cmds));
    transEngine trans_JOIN_INNER_TD_2611_out;
    trans_JOIN_INNER_TD_2611_out.setq(q_h);
    q_h.finish();
    transEngine trans_JOIN_INNER_TD_3935;
    trans_JOIN_INNER_TD_3935.setq(q_h);
    trans_JOIN_INNER_TD_3935.add(&(cfg_JOIN_INNER_TD_3935_cmds));
    q_h.finish();
    transEngine trans_Aggregate_TD_7555;
    trans_Aggregate_TD_7555.setq(q_a);
    trans_Aggregate_TD_7555.add(&(cfg_Aggregate_TD_7555_cmds));
    transEngine trans_Aggregate_TD_7555_out;
    trans_Aggregate_TD_7555_out.setq(q_a);
    q_a.finish();
    // ****************************** Events **************************** // 
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_2611;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_2611;
    std::vector<cl::Event> events_JOIN_INNER_TD_2611;
    events_h2d_wr_JOIN_INNER_TD_2611.resize(1);
    events_d2h_rd_JOIN_INNER_TD_2611.resize(1);
    events_JOIN_INNER_TD_2611.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_2611;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_2611;
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_3935;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_3935;
    std::vector<cl::Event> events_JOIN_INNER_TD_3935;
    events_h2d_wr_JOIN_INNER_TD_3935.resize(1);
    events_d2h_rd_JOIN_INNER_TD_3935.resize(1);
    events_JOIN_INNER_TD_3935.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_3935;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_3935;
    std::vector<cl::Event> events_h2d_wr_Aggregate_TD_7555;
    std::vector<cl::Event> events_d2h_rd_Aggregate_TD_7555;
    std::vector<cl::Event> events_Aggregate_TD_7555;
    events_h2d_wr_Aggregate_TD_7555.resize(1);
    events_d2h_rd_Aggregate_TD_7555.resize(1);
    events_Aggregate_TD_7555.resize(1);
    std::vector<cl::Event> events_grp_Aggregate_TD_7555;
    std::vector<cl::Event> prev_events_grp_Aggregate_TD_7555;
    // **************************** Operations ************************** // 
    struct timeval tv_r_s, tv_r_e; 
    gettimeofday(&tv_r_s, 0); 

    struct timeval tv_r_Project_8_730_s, tv_r_Project_8_730_e;
    gettimeofday(&tv_r_Project_8_730_s, 0);
    SW_Project_TD_8215(tbl_SerializeFromObject_TD_9452_input, tbl_Project_TD_8215_output);
    gettimeofday(&tv_r_Project_8_730_e, 0);

    struct timeval tv_r_Aggregate_7_974_s, tv_r_Aggregate_7_974_e;
    gettimeofday(&tv_r_Aggregate_7_974_s, 0);
    trans_Aggregate_TD_7555.add(&(tbl_Project_TD_8215_output));
    trans_Aggregate_TD_7555.host2dev(0, &(prev_events_grp_Aggregate_TD_7555), &(events_h2d_wr_Aggregate_TD_7555[0]));
    events_grp_Aggregate_TD_7555.push_back(events_h2d_wr_Aggregate_TD_7555[0]);
    krnl_Aggregate_TD_7555.run(0, &(events_grp_Aggregate_TD_7555), &(events_Aggregate_TD_7555[0]));
    
    trans_Aggregate_TD_7555_out.add(&(tbl_Aggregate_TD_7555_output_preprocess));
    trans_Aggregate_TD_7555_out.dev2host(0, &(events_Aggregate_TD_7555), &(events_d2h_rd_Aggregate_TD_7555[0]));
    q_a.flush();
    q_a.finish();
    
    SW_Aggregate_TD_7555_consolidate(tbl_Aggregate_TD_7555_output_preprocess, tbl_Aggregate_TD_7555_output);
    gettimeofday(&tv_r_Aggregate_7_974_e, 0);

    struct timeval tv_r_Filter_6_800_s, tv_r_Filter_6_800_e;
    gettimeofday(&tv_r_Filter_6_800_s, 0);
    SW_Filter_TD_6726(tbl_Aggregate_TD_7555_output, tbl_Filter_TD_6726_output);
    gettimeofday(&tv_r_Filter_6_800_e, 0);

    struct timeval tv_r_JOIN_LEFTSEMI_5_443_s, tv_r_JOIN_LEFTSEMI_5_443_e;
    gettimeofday(&tv_r_JOIN_LEFTSEMI_5_443_s, 0);
    SW_JOIN_LEFTSEMI_TD_5796(tbl_SerializeFromObject_TD_7614_input, tbl_Filter_TD_6726_output, tbl_JOIN_LEFTSEMI_TD_5796_output);
    gettimeofday(&tv_r_JOIN_LEFTSEMI_5_443_e, 0);

    struct timeval tv_r_JOIN_LEFTSEMI_4_101_s, tv_r_JOIN_LEFTSEMI_4_101_e;
    gettimeofday(&tv_r_JOIN_LEFTSEMI_4_101_s, 0);
    SW_JOIN_LEFTSEMI_TD_4655(tbl_SerializeFromObject_TD_6621_input, tbl_Filter_TD_6726_output, tbl_JOIN_LEFTSEMI_TD_4655_output);
    gettimeofday(&tv_r_JOIN_LEFTSEMI_4_101_e, 0);

    struct timeval tv_r_Project_4_984_s, tv_r_Project_4_984_e;
    gettimeofday(&tv_r_Project_4_984_s, 0);
    SW_Project_TD_4104(tbl_JOIN_LEFTSEMI_TD_5796_output, tbl_Project_TD_4104_output);
    gettimeofday(&tv_r_Project_4_984_e, 0);

    struct timeval tv_r_Project_4_75_s, tv_r_Project_4_75_e;
    gettimeofday(&tv_r_Project_4_75_s, 0);
    SW_Project_TD_4345(tbl_SerializeFromObject_TD_666_input_stringRowIDSubstitute, tbl_Project_TD_4345_output);
    gettimeofday(&tv_r_Project_4_75_e, 0);

    struct timeval tv_r_Project_3_881_s, tv_r_Project_3_881_e;
    gettimeofday(&tv_r_Project_3_881_s, 0);
    SW_Project_TD_3477(tbl_JOIN_LEFTSEMI_TD_4655_output, tbl_Project_TD_3477_output);
    gettimeofday(&tv_r_Project_3_881_e, 0);

    struct timeval tv_r_JOIN_INNER_3_603_s, tv_r_JOIN_INNER_3_603_e;
    gettimeofday(&tv_r_JOIN_INNER_3_603_s, 0);
    trans_JOIN_INNER_TD_3935.add(&(tbl_Project_TD_4345_output));
    trans_JOIN_INNER_TD_3935.add(&(tbl_Project_TD_4104_output));
    trans_JOIN_INNER_TD_3935.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_3935), &(events_h2d_wr_JOIN_INNER_TD_3935[0]));
    events_grp_JOIN_INNER_TD_3935.push_back(events_h2d_wr_JOIN_INNER_TD_3935[0]);
    krnl_JOIN_INNER_TD_3935.run(0, &(events_grp_JOIN_INNER_TD_3935), &(events_JOIN_INNER_TD_3935[0]));
    gettimeofday(&tv_r_JOIN_INNER_3_603_e, 0);

    struct timeval tv_r_JOIN_INNER_2_731_s, tv_r_JOIN_INNER_2_731_e;
    gettimeofday(&tv_r_JOIN_INNER_2_731_s, 0);
    prev_events_grp_JOIN_INNER_TD_2611.push_back(events_h2d_wr_JOIN_INNER_TD_3935[0]);
    trans_JOIN_INNER_TD_2611.add(&(tbl_Project_TD_3477_output));
    trans_JOIN_INNER_TD_2611.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_2611), &(events_h2d_wr_JOIN_INNER_TD_2611[0]));
    events_grp_JOIN_INNER_TD_2611.push_back(events_h2d_wr_JOIN_INNER_TD_2611[0]);
    events_grp_JOIN_INNER_TD_2611.push_back(events_JOIN_INNER_TD_3935[0]);
    krnl_JOIN_INNER_TD_2611.run(0, &(events_grp_JOIN_INNER_TD_2611), &(events_JOIN_INNER_TD_2611[0]));
    
    trans_JOIN_INNER_TD_2611_out.add(&(tbl_JOIN_INNER_TD_2611_output));
    trans_JOIN_INNER_TD_2611_out.dev2host(0, &(events_JOIN_INNER_TD_2611), &(events_d2h_rd_JOIN_INNER_TD_2611[0]));
    q_h.flush();
    q_h.finish();
    gettimeofday(&tv_r_JOIN_INNER_2_731_e, 0);

    struct timeval tv_r_Aggregate_1_494_s, tv_r_Aggregate_1_494_e;
    gettimeofday(&tv_r_Aggregate_1_494_s, 0);
    SW_Aggregate_TD_1464(tbl_JOIN_INNER_TD_2611_output, tbl_SerializeFromObject_TD_666_input, tbl_Aggregate_TD_1464_output);
    gettimeofday(&tv_r_Aggregate_1_494_e, 0);

    struct timeval tv_r_Sort_0_682_s, tv_r_Sort_0_682_e;
    gettimeofday(&tv_r_Sort_0_682_s, 0);
    SW_Sort_TD_0126(tbl_Aggregate_TD_1464_output, tbl_Sort_TD_0126_output);
    gettimeofday(&tv_r_Sort_0_682_e, 0);

    gettimeofday(&tv_r_e, 0); 
    // **************************** Print Execution Time ************************** // 
    std::cout << "Project_8: " << tvdiff(&tv_r_Project_8_730_s, &tv_r_Project_8_730_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_9452_input: " << tbl_SerializeFromObject_TD_9452_input.getNumRow() << " " << std::endl; 

    std::cout << "Aggregate_7: " << tvdiff(&tv_r_Aggregate_7_974_s, &tv_r_Aggregate_7_974_e) / 1000.0 << " ms " 
     << "tbl_Project_TD_8215_output: " << tbl_Project_TD_8215_output.getNumRow() << " " << std::endl; 

    std::cout << "Filter_6: " << tvdiff(&tv_r_Filter_6_800_s, &tv_r_Filter_6_800_e) / 1000.0 << " ms " 
     << "tbl_Aggregate_TD_7555_output: " << tbl_Aggregate_TD_7555_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_LEFTSEMI_5: " << tvdiff(&tv_r_JOIN_LEFTSEMI_5_443_s, &tv_r_JOIN_LEFTSEMI_5_443_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_7614_input: " << tbl_SerializeFromObject_TD_7614_input.getNumRow() << " " << "tbl_Filter_TD_6726_output: " << tbl_Filter_TD_6726_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_LEFTSEMI_4: " << tvdiff(&tv_r_JOIN_LEFTSEMI_4_101_s, &tv_r_JOIN_LEFTSEMI_4_101_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_6621_input: " << tbl_SerializeFromObject_TD_6621_input.getNumRow() << " " << "tbl_Filter_TD_6726_output: " << tbl_Filter_TD_6726_output.getNumRow() << " " << std::endl; 

    std::cout << "Project_4: " << tvdiff(&tv_r_Project_4_984_s, &tv_r_Project_4_984_e) / 1000.0 << " ms " 
     << "tbl_JOIN_LEFTSEMI_TD_5796_output: " << tbl_JOIN_LEFTSEMI_TD_5796_output.getNumRow() << " " << std::endl; 

    std::cout << "Project_4: " << tvdiff(&tv_r_Project_4_75_s, &tv_r_Project_4_75_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_666_input_stringRowIDSubstitute: " << tbl_SerializeFromObject_TD_666_input_stringRowIDSubstitute.getNumRow() << " " << std::endl; 

    std::cout << "Project_3: " << tvdiff(&tv_r_Project_3_881_s, &tv_r_Project_3_881_e) / 1000.0 << " ms " 
     << "tbl_JOIN_LEFTSEMI_TD_4655_output: " << tbl_JOIN_LEFTSEMI_TD_4655_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_3: " << tvdiff(&tv_r_JOIN_INNER_3_603_s, &tv_r_JOIN_INNER_3_603_e) / 1000.0 << " ms " 
     << "tbl_Project_TD_4345_output: " << tbl_Project_TD_4345_output.getNumRow() << " " << "tbl_Project_TD_4104_output: " << tbl_Project_TD_4104_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_2: " << tvdiff(&tv_r_JOIN_INNER_2_731_s, &tv_r_JOIN_INNER_2_731_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_3935_output: " << tbl_JOIN_INNER_TD_3935_output.getNumRow() << " " << "tbl_Project_TD_3477_output: " << tbl_Project_TD_3477_output.getNumRow() << " " << std::endl; 

    std::cout << "Aggregate_1: " << tvdiff(&tv_r_Aggregate_1_494_s, &tv_r_Aggregate_1_494_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_2611_output: " << tbl_JOIN_INNER_TD_2611_output.getNumRow() << " " << std::endl; 

    std::cout << "Sort_0: " << tvdiff(&tv_r_Sort_0_682_s, &tv_r_Sort_0_682_e) / 1000.0 << " ms " 
     << "tbl_Aggregate_TD_1464_output: " << tbl_Aggregate_TD_1464_output.getNumRow() << " " << std::endl; 

    std::cout << std::endl << " Total execution time: " << tvdiff(&tv_r_s, &tv_r_e) / 1000 << " ms"; 

    std::cout << std::endl << " Spark elapsed time: " << 48.185394 * 1000 << "ms" << std::endl; 
    return 0; 
}
