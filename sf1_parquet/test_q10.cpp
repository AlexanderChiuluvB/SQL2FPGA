// number of overlays (w/o fusion): 3 
// number of overlays (w/ fusion): 3 
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

#include "cfgFunc_q10.hpp" 
#include "q10.hpp" 

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
    std::cout << "NOTE:running query #10\n."; 
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
    // ****************************** Tables **************************** // 
    Table tbl_Sort_TD_0873_output("tbl_Sort_TD_0873_output", 6100000, 5, "");
    tbl_Sort_TD_0873_output.allocateHost();
    Table tbl_Aggregate_TD_1445_output("tbl_Aggregate_TD_1445_output", 6100000, 5, "");
    tbl_Aggregate_TD_1445_output.allocateHost();
    Table tbl_JOIN_INNER_TD_2546_output("tbl_JOIN_INNER_TD_2546_output", 114347, 6, "");
    tbl_JOIN_INNER_TD_2546_output.allocateHost();
    Table tbl_JOIN_INNER_TD_3336_output("tbl_JOIN_INNER_TD_3336_output", 114347, 6, "");
    tbl_JOIN_INNER_TD_3336_output.allocateHost();
    Table tbl_SerializeFromObject_TD_3408_input_stringRowIDSubstitute;
    tbl_SerializeFromObject_TD_3408_input_stringRowIDSubstitute = Table("nation", nation_n, 2, in_dir);
    tbl_SerializeFromObject_TD_3408_input_stringRowIDSubstitute.addCol("n_nationkey", 4);
    tbl_SerializeFromObject_TD_3408_input_stringRowIDSubstitute.addCol("n_name", 4, 1, 0);
    tbl_SerializeFromObject_TD_3408_input_stringRowIDSubstitute.allocateHost();
    tbl_SerializeFromObject_TD_3408_input_stringRowIDSubstitute.loadHost();
    Table tbl_SerializeFromObject_TD_3408_input;
    tbl_SerializeFromObject_TD_3408_input = Table("nation", nation_n, 2, in_dir);
    tbl_SerializeFromObject_TD_3408_input.addCol("n_nationkey", 4);
    tbl_SerializeFromObject_TD_3408_input.addCol("n_name", TPCH_READ_NATION_LEN+1);
    tbl_SerializeFromObject_TD_3408_input.allocateHost();
    tbl_SerializeFromObject_TD_3408_input.loadHost();
    Table tbl_JOIN_INNER_TD_4680_output("tbl_JOIN_INNER_TD_4680_output", 57111, 5, "");
    tbl_JOIN_INNER_TD_4680_output.allocateHost();
    Table tbl_Filter_TD_4263_output("tbl_Filter_TD_4263_output", 6100000, 3, "");
    tbl_Filter_TD_4263_output.allocateHost();
    Table tbl_SerializeFromObject_TD_5424_input_stringRowIDSubstitute;
    tbl_SerializeFromObject_TD_5424_input_stringRowIDSubstitute = Table("customer", customer_n, 4, in_dir);
    tbl_SerializeFromObject_TD_5424_input_stringRowIDSubstitute.addCol("c_custkey", 4);
    tbl_SerializeFromObject_TD_5424_input_stringRowIDSubstitute.addCol("c_name", 4, 1, 0);
    tbl_SerializeFromObject_TD_5424_input_stringRowIDSubstitute.addCol("c_nationkey", 4);
    tbl_SerializeFromObject_TD_5424_input_stringRowIDSubstitute.addCol("c_acctbal", 4);
    tbl_SerializeFromObject_TD_5424_input_stringRowIDSubstitute.allocateHost();
    tbl_SerializeFromObject_TD_5424_input_stringRowIDSubstitute.loadHost();
    Table tbl_SerializeFromObject_TD_5424_input;
    tbl_SerializeFromObject_TD_5424_input = Table("customer", customer_n, 4, in_dir);
    tbl_SerializeFromObject_TD_5424_input.addCol("c_custkey", 4);
    tbl_SerializeFromObject_TD_5424_input.addCol("c_name", TPCH_READ_C_NAME_LEN+1);
    tbl_SerializeFromObject_TD_5424_input.addCol("c_nationkey", 4);
    tbl_SerializeFromObject_TD_5424_input.addCol("c_acctbal", 4);
    tbl_SerializeFromObject_TD_5424_input.allocateHost();
    tbl_SerializeFromObject_TD_5424_input.loadHost();
    Table tbl_Filter_TD_555_output("tbl_Filter_TD_555_output", 6100000, 2, "");
    tbl_Filter_TD_555_output.allocateHost();
    Table tbl_SerializeFromObject_TD_5430_input;
    tbl_SerializeFromObject_TD_5430_input = Table("lineitem", lineitem_n, 4, in_dir);
    tbl_SerializeFromObject_TD_5430_input.addCol("l_orderkey", 4);
    tbl_SerializeFromObject_TD_5430_input.addCol("l_extendedprice", 4);
    tbl_SerializeFromObject_TD_5430_input.addCol("l_discount", 4);
    tbl_SerializeFromObject_TD_5430_input.addCol("l_returnflag", 4);
    tbl_SerializeFromObject_TD_5430_input.allocateHost();
    tbl_SerializeFromObject_TD_5430_input.loadHost();
    Table tbl_SerializeFromObject_TD_6957_input;
    tbl_SerializeFromObject_TD_6957_input = Table("orders", orders_n, 3, in_dir);
    tbl_SerializeFromObject_TD_6957_input.addCol("o_orderkey", 4);
    tbl_SerializeFromObject_TD_6957_input.addCol("o_custkey", 4);
    tbl_SerializeFromObject_TD_6957_input.addCol("o_orderdate", 4);
    tbl_SerializeFromObject_TD_6957_input.allocateHost();
    tbl_SerializeFromObject_TD_6957_input.loadHost();
    // ********************** Allocate Device Buffer ******************** // 
    tbl_JOIN_INNER_TD_2546_output.allocateDevBuffer(context_h, 32);
    tbl_JOIN_INNER_TD_3336_output.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_3408_input_stringRowIDSubstitute.allocateDevBuffer(context_h, 32);
    tbl_JOIN_INNER_TD_4680_output.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_4263_output.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_5424_input_stringRowIDSubstitute.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_555_output.allocateDevBuffer(context_h, 32);
    // ****************************** Config **************************** // 
    cfgCmd cfg_JOIN_INNER_TD_2546_cmds;
    cfg_JOIN_INNER_TD_2546_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_2546_gqe_join (cfg_JOIN_INNER_TD_2546_cmds.cmd);
    cfg_JOIN_INNER_TD_2546_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_INNER_TD_3336_cmds;
    cfg_JOIN_INNER_TD_3336_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_3336_gqe_join (cfg_JOIN_INNER_TD_3336_cmds.cmd);
    cfg_JOIN_INNER_TD_3336_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_INNER_TD_4680_cmds;
    cfg_JOIN_INNER_TD_4680_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_4680_gqe_join (cfg_JOIN_INNER_TD_4680_cmds.cmd);
    cfg_JOIN_INNER_TD_4680_cmds.allocateDevBuffer(context_h, 32);
    // *************************** Kernel Setup ************************* // 
    bufferTmp buftmp_h(context_h); 
    buftmp_h.initBuffer(q_h); 
    std::cout << std::endl; 
    krnlEngine krnl_JOIN_INNER_TD_2546;
    krnl_JOIN_INNER_TD_2546 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_2546.setup(tbl_SerializeFromObject_TD_3408_input_stringRowIDSubstitute, tbl_JOIN_INNER_TD_3336_output, tbl_JOIN_INNER_TD_2546_output, cfg_JOIN_INNER_TD_2546_cmds, buftmp_h);
    krnlEngine krnl_JOIN_INNER_TD_3336;
    krnl_JOIN_INNER_TD_3336 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_3336.setup(tbl_Filter_TD_4263_output, tbl_JOIN_INNER_TD_4680_output, tbl_JOIN_INNER_TD_3336_output, cfg_JOIN_INNER_TD_3336_cmds, buftmp_h);
    krnlEngine krnl_JOIN_INNER_TD_4680;
    krnl_JOIN_INNER_TD_4680 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_4680.setup(tbl_Filter_TD_555_output, tbl_SerializeFromObject_TD_5424_input_stringRowIDSubstitute, tbl_JOIN_INNER_TD_4680_output, cfg_JOIN_INNER_TD_4680_cmds, buftmp_h);
    // ************************** Transfer Engine *********************** // 
    transEngine trans_JOIN_INNER_TD_2546;
    trans_JOIN_INNER_TD_2546.setq(q_h);
    trans_JOIN_INNER_TD_2546.add(&(cfg_JOIN_INNER_TD_2546_cmds));
    trans_JOIN_INNER_TD_2546.add(&(tbl_SerializeFromObject_TD_3408_input_stringRowIDSubstitute));
    transEngine trans_JOIN_INNER_TD_2546_out;
    trans_JOIN_INNER_TD_2546_out.setq(q_h);
    q_h.finish();
    transEngine trans_JOIN_INNER_TD_3336;
    trans_JOIN_INNER_TD_3336.setq(q_h);
    trans_JOIN_INNER_TD_3336.add(&(cfg_JOIN_INNER_TD_3336_cmds));
    q_h.finish();
    transEngine trans_JOIN_INNER_TD_4680;
    trans_JOIN_INNER_TD_4680.setq(q_h);
    trans_JOIN_INNER_TD_4680.add(&(cfg_JOIN_INNER_TD_4680_cmds));
    trans_JOIN_INNER_TD_4680.add(&(tbl_SerializeFromObject_TD_5424_input_stringRowIDSubstitute));
    q_h.finish();
    // ****************************** Events **************************** // 
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_2546;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_2546;
    std::vector<cl::Event> events_JOIN_INNER_TD_2546;
    events_h2d_wr_JOIN_INNER_TD_2546.resize(1);
    events_d2h_rd_JOIN_INNER_TD_2546.resize(1);
    events_JOIN_INNER_TD_2546.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_2546;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_2546;
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_3336;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_3336;
    std::vector<cl::Event> events_JOIN_INNER_TD_3336;
    events_h2d_wr_JOIN_INNER_TD_3336.resize(1);
    events_d2h_rd_JOIN_INNER_TD_3336.resize(1);
    events_JOIN_INNER_TD_3336.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_3336;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_3336;
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_4680;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_4680;
    std::vector<cl::Event> events_JOIN_INNER_TD_4680;
    events_h2d_wr_JOIN_INNER_TD_4680.resize(1);
    events_d2h_rd_JOIN_INNER_TD_4680.resize(1);
    events_JOIN_INNER_TD_4680.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_4680;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_4680;
    // **************************** Operations ************************** // 
    struct timeval tv_r_s, tv_r_e; 
    gettimeofday(&tv_r_s, 0); 

    struct timeval tv_r_Filter_5_128_s, tv_r_Filter_5_128_e;
    gettimeofday(&tv_r_Filter_5_128_s, 0);
    SW_Filter_TD_555(tbl_SerializeFromObject_TD_6957_input, tbl_Filter_TD_555_output);
    gettimeofday(&tv_r_Filter_5_128_e, 0);

    struct timeval tv_r_Filter_4_846_s, tv_r_Filter_4_846_e;
    gettimeofday(&tv_r_Filter_4_846_s, 0);
    SW_Filter_TD_4263(tbl_SerializeFromObject_TD_5430_input, tbl_Filter_TD_4263_output);
    gettimeofday(&tv_r_Filter_4_846_e, 0);

    struct timeval tv_r_JOIN_INNER_4_751_s, tv_r_JOIN_INNER_4_751_e;
    gettimeofday(&tv_r_JOIN_INNER_4_751_s, 0);
    trans_JOIN_INNER_TD_4680.add(&(tbl_Filter_TD_555_output));
    trans_JOIN_INNER_TD_4680.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_4680), &(events_h2d_wr_JOIN_INNER_TD_4680[0]));
    events_grp_JOIN_INNER_TD_4680.push_back(events_h2d_wr_JOIN_INNER_TD_4680[0]);
    krnl_JOIN_INNER_TD_4680.run(0, &(events_grp_JOIN_INNER_TD_4680), &(events_JOIN_INNER_TD_4680[0]));
    gettimeofday(&tv_r_JOIN_INNER_4_751_e, 0);

    struct timeval tv_r_JOIN_INNER_3_171_s, tv_r_JOIN_INNER_3_171_e;
    gettimeofday(&tv_r_JOIN_INNER_3_171_s, 0);
    prev_events_grp_JOIN_INNER_TD_3336.push_back(events_h2d_wr_JOIN_INNER_TD_4680[0]);
    trans_JOIN_INNER_TD_3336.add(&(tbl_Filter_TD_4263_output));
    trans_JOIN_INNER_TD_3336.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_3336), &(events_h2d_wr_JOIN_INNER_TD_3336[0]));
    events_grp_JOIN_INNER_TD_3336.push_back(events_h2d_wr_JOIN_INNER_TD_3336[0]);
    events_grp_JOIN_INNER_TD_3336.push_back(events_JOIN_INNER_TD_4680[0]);
    krnl_JOIN_INNER_TD_3336.run(0, &(events_grp_JOIN_INNER_TD_3336), &(events_JOIN_INNER_TD_3336[0]));
    gettimeofday(&tv_r_JOIN_INNER_3_171_e, 0);

    struct timeval tv_r_JOIN_INNER_2_624_s, tv_r_JOIN_INNER_2_624_e;
    gettimeofday(&tv_r_JOIN_INNER_2_624_s, 0);
    prev_events_grp_JOIN_INNER_TD_2546.push_back(events_h2d_wr_JOIN_INNER_TD_3336[0]);
    trans_JOIN_INNER_TD_2546.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_2546), &(events_h2d_wr_JOIN_INNER_TD_2546[0]));
    events_grp_JOIN_INNER_TD_2546.push_back(events_h2d_wr_JOIN_INNER_TD_2546[0]);
    events_grp_JOIN_INNER_TD_2546.push_back(events_JOIN_INNER_TD_3336[0]);
    krnl_JOIN_INNER_TD_2546.run(0, &(events_grp_JOIN_INNER_TD_2546), &(events_JOIN_INNER_TD_2546[0]));
    
    trans_JOIN_INNER_TD_2546_out.add(&(tbl_JOIN_INNER_TD_2546_output));
    trans_JOIN_INNER_TD_2546_out.dev2host(0, &(events_JOIN_INNER_TD_2546), &(events_d2h_rd_JOIN_INNER_TD_2546[0]));
    q_h.flush();
    q_h.finish();
    gettimeofday(&tv_r_JOIN_INNER_2_624_e, 0);

    struct timeval tv_r_Aggregate_1_4_s, tv_r_Aggregate_1_4_e;
    gettimeofday(&tv_r_Aggregate_1_4_s, 0);
    SW_Aggregate_TD_1445(tbl_JOIN_INNER_TD_2546_output, tbl_SerializeFromObject_TD_5424_input, tbl_SerializeFromObject_TD_6957_input, tbl_SerializeFromObject_TD_5430_input, tbl_SerializeFromObject_TD_3408_input, tbl_Aggregate_TD_1445_output);
    gettimeofday(&tv_r_Aggregate_1_4_e, 0);

    struct timeval tv_r_Sort_0_39_s, tv_r_Sort_0_39_e;
    gettimeofday(&tv_r_Sort_0_39_s, 0);
    SW_Sort_TD_0873(tbl_Aggregate_TD_1445_output, tbl_Sort_TD_0873_output);
    gettimeofday(&tv_r_Sort_0_39_e, 0);

    gettimeofday(&tv_r_e, 0); 
    // **************************** Print Execution Time ************************** // 
    std::cout << "Filter_5: " << tvdiff(&tv_r_Filter_5_128_s, &tv_r_Filter_5_128_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_6957_input: " << tbl_SerializeFromObject_TD_6957_input.getNumRow() << " " << std::endl; 

    std::cout << "Filter_4: " << tvdiff(&tv_r_Filter_4_846_s, &tv_r_Filter_4_846_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_5430_input: " << tbl_SerializeFromObject_TD_5430_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_4: " << tvdiff(&tv_r_JOIN_INNER_4_751_s, &tv_r_JOIN_INNER_4_751_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_5424_input_stringRowIDSubstitute: " << tbl_SerializeFromObject_TD_5424_input_stringRowIDSubstitute.getNumRow() << " " << "tbl_Filter_TD_555_output: " << tbl_Filter_TD_555_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_3: " << tvdiff(&tv_r_JOIN_INNER_3_171_s, &tv_r_JOIN_INNER_3_171_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_4680_output: " << tbl_JOIN_INNER_TD_4680_output.getNumRow() << " " << "tbl_Filter_TD_4263_output: " << tbl_Filter_TD_4263_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_2: " << tvdiff(&tv_r_JOIN_INNER_2_624_s, &tv_r_JOIN_INNER_2_624_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_3336_output: " << tbl_JOIN_INNER_TD_3336_output.getNumRow() << " " << "tbl_SerializeFromObject_TD_3408_input_stringRowIDSubstitute: " << tbl_SerializeFromObject_TD_3408_input_stringRowIDSubstitute.getNumRow() << " " << std::endl; 

    std::cout << "Aggregate_1: " << tvdiff(&tv_r_Aggregate_1_4_s, &tv_r_Aggregate_1_4_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_2546_output: " << tbl_JOIN_INNER_TD_2546_output.getNumRow() << " " << std::endl; 

    std::cout << "Sort_0: " << tvdiff(&tv_r_Sort_0_39_s, &tv_r_Sort_0_39_e) / 1000.0 << " ms " 
     << "tbl_Aggregate_TD_1445_output: " << tbl_Aggregate_TD_1445_output.getNumRow() << " " << std::endl; 

    std::cout << std::endl << " Total execution time: " << tvdiff(&tv_r_s, &tv_r_e) / 1000 << " ms"; 

    std::cout << std::endl << " Spark elapsed time: " << 39.68206 * 1000 << "ms" << std::endl; 
    return 0; 
}
