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

#include "cfgFunc_q2.hpp" 
#include "q2.hpp" 

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
    std::cout << "NOTE:running query #2\n."; 
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
    Table tbl_Sort_TD_0144_output("tbl_Sort_TD_0144_output", 6100000, 8, "");
    tbl_Sort_TD_0144_output.allocateHost();
    Table tbl_JOIN_INNER_TD_1987_output("tbl_JOIN_INNER_TD_1987_output", 6100000, 8, "");
    tbl_JOIN_INNER_TD_1987_output.allocateHost();
    Table tbl_JOIN_INNER_TD_2792_output("tbl_JOIN_INNER_TD_2792_output", 6100000, 9, "");
    tbl_JOIN_INNER_TD_2792_output.allocateHost();
    Table tbl_JOIN_INNER_TD_394_output("tbl_JOIN_INNER_TD_394_output", 6100000, 8, "");
    tbl_JOIN_INNER_TD_394_output.allocateHost();
    Table tbl_SerializeFromObject_TD_3961_input_stringRowIDSubstitute;
    tbl_SerializeFromObject_TD_3961_input_stringRowIDSubstitute = Table("nation", nation_n, 3, in_dir);
    tbl_SerializeFromObject_TD_3961_input_stringRowIDSubstitute.addCol("n_nationkey", 4);
    tbl_SerializeFromObject_TD_3961_input_stringRowIDSubstitute.addCol("n_name", 4, 1, 0);
    tbl_SerializeFromObject_TD_3961_input_stringRowIDSubstitute.addCol("n_regionkey", 4);
    tbl_SerializeFromObject_TD_3961_input_stringRowIDSubstitute.allocateHost();
    tbl_SerializeFromObject_TD_3961_input_stringRowIDSubstitute.loadHost();
    Table tbl_SerializeFromObject_TD_3961_input;
    tbl_SerializeFromObject_TD_3961_input = Table("nation", nation_n, 3, in_dir);
    tbl_SerializeFromObject_TD_3961_input.addCol("n_nationkey", 4);
    tbl_SerializeFromObject_TD_3961_input.addCol("n_name", TPCH_READ_NATION_LEN+1);
    tbl_SerializeFromObject_TD_3961_input.addCol("n_regionkey", 4);
    tbl_SerializeFromObject_TD_3961_input.allocateHost();
    tbl_SerializeFromObject_TD_3961_input.loadHost();
    Table tbl_JOIN_INNER_TD_4283_output("tbl_JOIN_INNER_TD_4283_output", 6100000, 3, "");
    tbl_JOIN_INNER_TD_4283_output.allocateHost();
    Table tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute;
    tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute = Table("supplier", supplier_n, 7, in_dir);
    tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute.addCol("s_suppkey", 4);
    tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute.addCol("s_name", 4, 1, 0);
    tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute.addCol("s_address", 4, 1, 0);
    tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute.addCol("s_nationkey", 4);
    tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute.addCol("s_phone", 4, 1, 0);
    tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute.addCol("s_acctbal", 4);
    tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute.addCol("s_comment", 4, 1, 0);
    tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute.allocateHost();
    tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute.loadHost();
    Table tbl_SerializeFromObject_TD_4583_input;
    tbl_SerializeFromObject_TD_4583_input = Table("supplier", supplier_n, 7, in_dir);
    tbl_SerializeFromObject_TD_4583_input.addCol("s_suppkey", 4);
    tbl_SerializeFromObject_TD_4583_input.addCol("s_name", TPCH_READ_S_NAME_LEN+1);
    tbl_SerializeFromObject_TD_4583_input.addCol("s_address", TPCH_READ_S_ADDR_MAX+1);
    tbl_SerializeFromObject_TD_4583_input.addCol("s_nationkey", 4);
    tbl_SerializeFromObject_TD_4583_input.addCol("s_phone", TPCH_READ_PHONE_LEN+1);
    tbl_SerializeFromObject_TD_4583_input.addCol("s_acctbal", 4);
    tbl_SerializeFromObject_TD_4583_input.addCol("s_comment", TPCH_READ_S_CMNT_MAX+1);
    tbl_SerializeFromObject_TD_4583_input.allocateHost();
    tbl_SerializeFromObject_TD_4583_input.loadHost();
    Table tbl_JOIN_INNER_TD_5202_output("tbl_JOIN_INNER_TD_5202_output", 628, 4, "");
    tbl_JOIN_INNER_TD_5202_output.allocateHost();
    Table tbl_Aggregate_TD_6742_output("tbl_Aggregate_TD_6742_output", 6100000, 2, "");
    tbl_Aggregate_TD_6742_output.allocateHost();
    Table tbl_Filter_TD_6426_output("tbl_Filter_TD_6426_output", 6100000, 2, "");
    tbl_Filter_TD_6426_output.allocateHost();
    Table tbl_JOIN_INNER_TD_7289_output("tbl_JOIN_INNER_TD_7289_output", 5, 2, "");
    tbl_JOIN_INNER_TD_7289_output.allocateHost();
    Table tbl_SerializeFromObject_TD_7781_input;
    tbl_SerializeFromObject_TD_7781_input = Table("part", part_n, 4, in_dir);
    tbl_SerializeFromObject_TD_7781_input.addCol("p_partkey", 4);
    tbl_SerializeFromObject_TD_7781_input.addCol("p_mfgr", TPCH_READ_P_MFG_LEN+1);
    tbl_SerializeFromObject_TD_7781_input.addCol("p_type", TPCH_READ_P_TYPE_LEN+1);
    tbl_SerializeFromObject_TD_7781_input.addCol("p_size", 4);
    tbl_SerializeFromObject_TD_7781_input.allocateHost();
    tbl_SerializeFromObject_TD_7781_input.loadHost();
    Table tbl_JOIN_INNER_TD_8484_output("tbl_JOIN_INNER_TD_8484_output", 2036, 3, "");
    tbl_JOIN_INNER_TD_8484_output.allocateHost();
    Table tbl_Filter_TD_8126_output("tbl_Filter_TD_8126_output", 6100000, 1, "");
    tbl_Filter_TD_8126_output.allocateHost();
    Table tbl_JOIN_INNER_TD_9373_output("tbl_JOIN_INNER_TD_9373_output", 162880, 3, "");
    tbl_JOIN_INNER_TD_9373_output.allocateHost();
    Table tbl_SerializeFromObject_TD_9293_input;
    tbl_SerializeFromObject_TD_9293_input = Table("nation", nation_n, 2, in_dir);
    tbl_SerializeFromObject_TD_9293_input.addCol("n_nationkey", 4);
    tbl_SerializeFromObject_TD_9293_input.addCol("n_regionkey", 4);
    tbl_SerializeFromObject_TD_9293_input.allocateHost();
    tbl_SerializeFromObject_TD_9293_input.loadHost();
    Table tbl_SerializeFromObject_TD_9370_input;
    tbl_SerializeFromObject_TD_9370_input = Table("region", region_n, 2, in_dir);
    tbl_SerializeFromObject_TD_9370_input.addCol("r_regionkey", 4);
    tbl_SerializeFromObject_TD_9370_input.addCol("r_name", TPCH_READ_REGION_LEN+1);
    tbl_SerializeFromObject_TD_9370_input.allocateHost();
    tbl_SerializeFromObject_TD_9370_input.loadHost();
    Table tbl_SerializeFromObject_TD_1026_input;
    tbl_SerializeFromObject_TD_1026_input = Table("partsupp", partsupp_n, 3, in_dir);
    tbl_SerializeFromObject_TD_1026_input.addCol("ps_partkey", 4);
    tbl_SerializeFromObject_TD_1026_input.addCol("ps_suppkey", 4);
    tbl_SerializeFromObject_TD_1026_input.addCol("ps_supplycost", 4);
    tbl_SerializeFromObject_TD_1026_input.allocateHost();
    tbl_SerializeFromObject_TD_1026_input.loadHost();
    Table tbl_SerializeFromObject_TD_10369_input;
    tbl_SerializeFromObject_TD_10369_input = Table("supplier", supplier_n, 2, in_dir);
    tbl_SerializeFromObject_TD_10369_input.addCol("s_suppkey", 4);
    tbl_SerializeFromObject_TD_10369_input.addCol("s_nationkey", 4);
    tbl_SerializeFromObject_TD_10369_input.allocateHost();
    tbl_SerializeFromObject_TD_10369_input.loadHost();
    // ********************** Allocate Device Buffer ******************** // 
    tbl_JOIN_INNER_TD_5202_output.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_6426_output.allocateDevBuffer(context_h, 32);
    tbl_JOIN_INNER_TD_7289_output.allocateDevBuffer(context_h, 32);
    tbl_JOIN_INNER_TD_8484_output.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_8126_output.allocateDevBuffer(context_h, 32);
    tbl_JOIN_INNER_TD_9373_output.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_9293_input.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_1026_input.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_10369_input.allocateDevBuffer(context_h, 32);
    // ****************************** Config **************************** // 
    cfgCmd cfg_JOIN_INNER_TD_5202_cmds;
    cfg_JOIN_INNER_TD_5202_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_5202_gqe_join (cfg_JOIN_INNER_TD_5202_cmds.cmd);
    cfg_JOIN_INNER_TD_5202_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_INNER_TD_7289_cmds;
    cfg_JOIN_INNER_TD_7289_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_7289_gqe_join (cfg_JOIN_INNER_TD_7289_cmds.cmd);
    cfg_JOIN_INNER_TD_7289_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_INNER_TD_8484_cmds;
    cfg_JOIN_INNER_TD_8484_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_8484_gqe_join (cfg_JOIN_INNER_TD_8484_cmds.cmd);
    cfg_JOIN_INNER_TD_8484_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_INNER_TD_9373_cmds;
    cfg_JOIN_INNER_TD_9373_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_9373_gqe_join (cfg_JOIN_INNER_TD_9373_cmds.cmd);
    cfg_JOIN_INNER_TD_9373_cmds.allocateDevBuffer(context_h, 32);
    // *************************** Kernel Setup ************************* // 
    bufferTmp buftmp_h(context_h); 
    buftmp_h.initBuffer(q_h); 
    std::cout << std::endl; 
    krnlEngine krnl_JOIN_INNER_TD_5202;
    krnl_JOIN_INNER_TD_5202 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_5202.setup(tbl_SerializeFromObject_TD_1026_input, tbl_Filter_TD_6426_output, tbl_JOIN_INNER_TD_5202_output, cfg_JOIN_INNER_TD_5202_cmds, buftmp_h);
    krnlEngine krnl_JOIN_INNER_TD_7289;
    krnl_JOIN_INNER_TD_7289 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_7289.setup(tbl_JOIN_INNER_TD_8484_output, tbl_Filter_TD_8126_output, tbl_JOIN_INNER_TD_7289_output, cfg_JOIN_INNER_TD_7289_cmds, buftmp_h);
    krnlEngine krnl_JOIN_INNER_TD_8484;
    krnl_JOIN_INNER_TD_8484 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_8484.setup(tbl_JOIN_INNER_TD_9373_output, tbl_SerializeFromObject_TD_9293_input, tbl_JOIN_INNER_TD_8484_output, cfg_JOIN_INNER_TD_8484_cmds, buftmp_h);
    krnlEngine krnl_JOIN_INNER_TD_9373;
    krnl_JOIN_INNER_TD_9373 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_9373.setup(tbl_SerializeFromObject_TD_1026_input, tbl_SerializeFromObject_TD_10369_input, tbl_JOIN_INNER_TD_9373_output, cfg_JOIN_INNER_TD_9373_cmds, buftmp_h);
    // ************************** Transfer Engine *********************** // 
    transEngine trans_JOIN_INNER_TD_5202;
    trans_JOIN_INNER_TD_5202.setq(q_h);
    trans_JOIN_INNER_TD_5202.add(&(cfg_JOIN_INNER_TD_5202_cmds));
    trans_JOIN_INNER_TD_5202.add(&(tbl_SerializeFromObject_TD_1026_input));
    transEngine trans_JOIN_INNER_TD_5202_out;
    trans_JOIN_INNER_TD_5202_out.setq(q_h);
    q_h.finish();
    transEngine trans_JOIN_INNER_TD_7289;
    trans_JOIN_INNER_TD_7289.setq(q_h);
    trans_JOIN_INNER_TD_7289.add(&(cfg_JOIN_INNER_TD_7289_cmds));
    transEngine trans_JOIN_INNER_TD_7289_out;
    trans_JOIN_INNER_TD_7289_out.setq(q_h);
    q_h.finish();
    transEngine trans_JOIN_INNER_TD_8484;
    trans_JOIN_INNER_TD_8484.setq(q_h);
    trans_JOIN_INNER_TD_8484.add(&(cfg_JOIN_INNER_TD_8484_cmds));
    trans_JOIN_INNER_TD_8484.add(&(tbl_SerializeFromObject_TD_9293_input));
    q_h.finish();
    transEngine trans_JOIN_INNER_TD_9373;
    trans_JOIN_INNER_TD_9373.setq(q_h);
    trans_JOIN_INNER_TD_9373.add(&(cfg_JOIN_INNER_TD_9373_cmds));
    trans_JOIN_INNER_TD_9373.add(&(tbl_SerializeFromObject_TD_1026_input));
    trans_JOIN_INNER_TD_9373.add(&(tbl_SerializeFromObject_TD_10369_input));
    q_h.finish();
    // ****************************** Events **************************** // 
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_5202;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_5202;
    std::vector<cl::Event> events_JOIN_INNER_TD_5202;
    events_h2d_wr_JOIN_INNER_TD_5202.resize(1);
    events_d2h_rd_JOIN_INNER_TD_5202.resize(1);
    events_JOIN_INNER_TD_5202.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_5202;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_5202;
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_7289;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_7289;
    std::vector<cl::Event> events_JOIN_INNER_TD_7289;
    events_h2d_wr_JOIN_INNER_TD_7289.resize(1);
    events_d2h_rd_JOIN_INNER_TD_7289.resize(1);
    events_JOIN_INNER_TD_7289.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_7289;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_7289;
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_8484;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_8484;
    std::vector<cl::Event> events_JOIN_INNER_TD_8484;
    events_h2d_wr_JOIN_INNER_TD_8484.resize(1);
    events_d2h_rd_JOIN_INNER_TD_8484.resize(1);
    events_JOIN_INNER_TD_8484.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_8484;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_8484;
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_9373;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_9373;
    std::vector<cl::Event> events_JOIN_INNER_TD_9373;
    events_h2d_wr_JOIN_INNER_TD_9373.resize(1);
    events_d2h_rd_JOIN_INNER_TD_9373.resize(1);
    events_JOIN_INNER_TD_9373.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_9373;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_9373;
    // **************************** Operations ************************** // 
    struct timeval tv_r_s, tv_r_e; 
    gettimeofday(&tv_r_s, 0); 

    struct timeval tv_r_JOIN_INNER_9_687_s, tv_r_JOIN_INNER_9_687_e;
    gettimeofday(&tv_r_JOIN_INNER_9_687_s, 0);
    trans_JOIN_INNER_TD_9373.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_9373), &(events_h2d_wr_JOIN_INNER_TD_9373[0]));
    events_grp_JOIN_INNER_TD_9373.push_back(events_h2d_wr_JOIN_INNER_TD_9373[0]);
    krnl_JOIN_INNER_TD_9373.run(0, &(events_grp_JOIN_INNER_TD_9373), &(events_JOIN_INNER_TD_9373[0]));
    gettimeofday(&tv_r_JOIN_INNER_9_687_e, 0);

    struct timeval tv_r_Filter_8_416_s, tv_r_Filter_8_416_e;
    gettimeofday(&tv_r_Filter_8_416_s, 0);
    SW_Filter_TD_8126(tbl_SerializeFromObject_TD_9370_input, tbl_Filter_TD_8126_output);
    gettimeofday(&tv_r_Filter_8_416_e, 0);

    struct timeval tv_r_JOIN_INNER_8_181_s, tv_r_JOIN_INNER_8_181_e;
    gettimeofday(&tv_r_JOIN_INNER_8_181_s, 0);
    prev_events_grp_JOIN_INNER_TD_8484.push_back(events_h2d_wr_JOIN_INNER_TD_9373[0]);
    trans_JOIN_INNER_TD_8484.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_8484), &(events_h2d_wr_JOIN_INNER_TD_8484[0]));
    events_grp_JOIN_INNER_TD_8484.push_back(events_h2d_wr_JOIN_INNER_TD_8484[0]);
    events_grp_JOIN_INNER_TD_8484.push_back(events_JOIN_INNER_TD_9373[0]);
    krnl_JOIN_INNER_TD_8484.run(0, &(events_grp_JOIN_INNER_TD_8484), &(events_JOIN_INNER_TD_8484[0]));
    gettimeofday(&tv_r_JOIN_INNER_8_181_e, 0);

    struct timeval tv_r_JOIN_INNER_7_852_s, tv_r_JOIN_INNER_7_852_e;
    gettimeofday(&tv_r_JOIN_INNER_7_852_s, 0);
    prev_events_grp_JOIN_INNER_TD_7289.push_back(events_h2d_wr_JOIN_INNER_TD_8484[0]);
    trans_JOIN_INNER_TD_7289.add(&(tbl_Filter_TD_8126_output));
    trans_JOIN_INNER_TD_7289.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_7289), &(events_h2d_wr_JOIN_INNER_TD_7289[0]));
    events_grp_JOIN_INNER_TD_7289.push_back(events_h2d_wr_JOIN_INNER_TD_7289[0]);
    events_grp_JOIN_INNER_TD_7289.push_back(events_JOIN_INNER_TD_8484[0]);
    krnl_JOIN_INNER_TD_7289.run(0, &(events_grp_JOIN_INNER_TD_7289), &(events_JOIN_INNER_TD_7289[0]));
    
    trans_JOIN_INNER_TD_7289_out.add(&(tbl_JOIN_INNER_TD_7289_output));
    trans_JOIN_INNER_TD_7289_out.dev2host(0, &(events_JOIN_INNER_TD_7289), &(events_d2h_rd_JOIN_INNER_TD_7289[0]));
    q_h.flush();
    q_h.finish();
    gettimeofday(&tv_r_JOIN_INNER_7_852_e, 0);

    struct timeval tv_r_Filter_6_259_s, tv_r_Filter_6_259_e;
    gettimeofday(&tv_r_Filter_6_259_s, 0);
    SW_Filter_TD_6426(tbl_SerializeFromObject_TD_7781_input, tbl_Filter_TD_6426_output);
    gettimeofday(&tv_r_Filter_6_259_e, 0);

    struct timeval tv_r_Aggregate_6_190_s, tv_r_Aggregate_6_190_e;
    gettimeofday(&tv_r_Aggregate_6_190_s, 0);
    SW_Aggregate_TD_6742(tbl_JOIN_INNER_TD_7289_output, tbl_Aggregate_TD_6742_output);
    gettimeofday(&tv_r_Aggregate_6_190_e, 0);

    struct timeval tv_r_JOIN_INNER_5_875_s, tv_r_JOIN_INNER_5_875_e;
    gettimeofday(&tv_r_JOIN_INNER_5_875_s, 0);
    trans_JOIN_INNER_TD_5202.add(&(tbl_Filter_TD_6426_output));
    trans_JOIN_INNER_TD_5202.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_5202), &(events_h2d_wr_JOIN_INNER_TD_5202[0]));
    events_grp_JOIN_INNER_TD_5202.push_back(events_h2d_wr_JOIN_INNER_TD_5202[0]);
    krnl_JOIN_INNER_TD_5202.run(0, &(events_grp_JOIN_INNER_TD_5202), &(events_JOIN_INNER_TD_5202[0]));
    
    trans_JOIN_INNER_TD_5202_out.add(&(tbl_JOIN_INNER_TD_5202_output));
    trans_JOIN_INNER_TD_5202_out.dev2host(0, &(events_JOIN_INNER_TD_5202), &(events_d2h_rd_JOIN_INNER_TD_5202[0]));
    q_h.flush();
    q_h.finish();
    gettimeofday(&tv_r_JOIN_INNER_5_875_e, 0);

    struct timeval tv_r_JOIN_INNER_4_787_s, tv_r_JOIN_INNER_4_787_e;
    gettimeofday(&tv_r_JOIN_INNER_4_787_s, 0);
    SW_JOIN_INNER_TD_4283(tbl_JOIN_INNER_TD_5202_output, tbl_Aggregate_TD_6742_output, tbl_JOIN_INNER_TD_4283_output);
    gettimeofday(&tv_r_JOIN_INNER_4_787_e, 0);

    struct timeval tv_r_JOIN_INNER_3_101_s, tv_r_JOIN_INNER_3_101_e;
    gettimeofday(&tv_r_JOIN_INNER_3_101_s, 0);
    SW_JOIN_INNER_TD_394(tbl_JOIN_INNER_TD_4283_output, tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute, tbl_JOIN_INNER_TD_394_output);
    gettimeofday(&tv_r_JOIN_INNER_3_101_e, 0);

    struct timeval tv_r_JOIN_INNER_2_183_s, tv_r_JOIN_INNER_2_183_e;
    gettimeofday(&tv_r_JOIN_INNER_2_183_s, 0);
    SW_JOIN_INNER_TD_2792(tbl_JOIN_INNER_TD_394_output, tbl_SerializeFromObject_TD_3961_input_stringRowIDSubstitute, tbl_JOIN_INNER_TD_2792_output);
    gettimeofday(&tv_r_JOIN_INNER_2_183_e, 0);

    struct timeval tv_r_JOIN_INNER_1_198_s, tv_r_JOIN_INNER_1_198_e;
    gettimeofday(&tv_r_JOIN_INNER_1_198_s, 0);
    SW_JOIN_INNER_TD_1987(tbl_JOIN_INNER_TD_2792_output, tbl_Filter_TD_8126_output, tbl_JOIN_INNER_TD_1987_output);
    gettimeofday(&tv_r_JOIN_INNER_1_198_e, 0);

    struct timeval tv_r_Sort_0_408_s, tv_r_Sort_0_408_e;
    gettimeofday(&tv_r_Sort_0_408_s, 0);
    SW_Sort_TD_0144(tbl_JOIN_INNER_TD_1987_output, tbl_SerializeFromObject_TD_7781_input, tbl_SerializeFromObject_TD_4583_input, tbl_SerializeFromObject_TD_3961_input, tbl_Sort_TD_0144_output);
    gettimeofday(&tv_r_Sort_0_408_e, 0);

    gettimeofday(&tv_r_e, 0); 
    // **************************** Print Execution Time ************************** // 
    std::cout << "JOIN_INNER_9: " << tvdiff(&tv_r_JOIN_INNER_9_687_s, &tv_r_JOIN_INNER_9_687_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_1026_input: " << tbl_SerializeFromObject_TD_1026_input.getNumRow() << " " << "tbl_SerializeFromObject_TD_10369_input: " << tbl_SerializeFromObject_TD_10369_input.getNumRow() << " " << std::endl; 

    std::cout << "Filter_8: " << tvdiff(&tv_r_Filter_8_416_s, &tv_r_Filter_8_416_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_9370_input: " << tbl_SerializeFromObject_TD_9370_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_8: " << tvdiff(&tv_r_JOIN_INNER_8_181_s, &tv_r_JOIN_INNER_8_181_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_9373_output: " << tbl_JOIN_INNER_TD_9373_output.getNumRow() << " " << "tbl_SerializeFromObject_TD_9293_input: " << tbl_SerializeFromObject_TD_9293_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_7: " << tvdiff(&tv_r_JOIN_INNER_7_852_s, &tv_r_JOIN_INNER_7_852_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_8484_output: " << tbl_JOIN_INNER_TD_8484_output.getNumRow() << " " << "tbl_Filter_TD_8126_output: " << tbl_Filter_TD_8126_output.getNumRow() << " " << std::endl; 

    std::cout << "Filter_6: " << tvdiff(&tv_r_Filter_6_259_s, &tv_r_Filter_6_259_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_7781_input: " << tbl_SerializeFromObject_TD_7781_input.getNumRow() << " " << std::endl; 

    std::cout << "Aggregate_6: " << tvdiff(&tv_r_Aggregate_6_190_s, &tv_r_Aggregate_6_190_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_7289_output: " << tbl_JOIN_INNER_TD_7289_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_5: " << tvdiff(&tv_r_JOIN_INNER_5_875_s, &tv_r_JOIN_INNER_5_875_e) / 1000.0 << " ms " 
     << "tbl_Filter_TD_6426_output: " << tbl_Filter_TD_6426_output.getNumRow() << " " << "tbl_SerializeFromObject_TD_1026_input: " << tbl_SerializeFromObject_TD_1026_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_4: " << tvdiff(&tv_r_JOIN_INNER_4_787_s, &tv_r_JOIN_INNER_4_787_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_5202_output: " << tbl_JOIN_INNER_TD_5202_output.getNumRow() << " " << "tbl_Aggregate_TD_6742_output: " << tbl_Aggregate_TD_6742_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_3: " << tvdiff(&tv_r_JOIN_INNER_3_101_s, &tv_r_JOIN_INNER_3_101_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_4283_output: " << tbl_JOIN_INNER_TD_4283_output.getNumRow() << " " << "tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute: " << tbl_SerializeFromObject_TD_4583_input_stringRowIDSubstitute.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_2: " << tvdiff(&tv_r_JOIN_INNER_2_183_s, &tv_r_JOIN_INNER_2_183_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_394_output: " << tbl_JOIN_INNER_TD_394_output.getNumRow() << " " << "tbl_SerializeFromObject_TD_3961_input_stringRowIDSubstitute: " << tbl_SerializeFromObject_TD_3961_input_stringRowIDSubstitute.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_1: " << tvdiff(&tv_r_JOIN_INNER_1_198_s, &tv_r_JOIN_INNER_1_198_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_2792_output: " << tbl_JOIN_INNER_TD_2792_output.getNumRow() << " " << "tbl_Filter_TD_8126_output: " << tbl_Filter_TD_8126_output.getNumRow() << " " << std::endl; 

    std::cout << "Sort_0: " << tvdiff(&tv_r_Sort_0_408_s, &tv_r_Sort_0_408_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_1987_output: " << tbl_JOIN_INNER_TD_1987_output.getNumRow() << " " << std::endl; 

    std::cout << std::endl << " Total execution time: " << tvdiff(&tv_r_s, &tv_r_e) / 1000 << " ms"; 

    std::cout << std::endl << " Spark elapsed time: " << 3.5092573 * 1000 << "ms" << std::endl; 
    return 0; 
}
