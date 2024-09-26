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

#include "cfgFunc_q21.hpp" 
#include "q21.hpp" 

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
    std::cout << "NOTE:running query #21\n."; 
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
    Table tbl_Sort_TD_0339_output("tbl_Sort_TD_0339_output", 6100000, 2, "");
    tbl_Sort_TD_0339_output.allocateHost();
    Table tbl_Aggregate_TD_1459_output("tbl_Aggregate_TD_1459_output", 6100000, 2, "");
    tbl_Aggregate_TD_1459_output.allocateHost();
    Table tbl_JOIN_INNER_TD_2744_output("tbl_JOIN_INNER_TD_2744_output", 25255, 1, "");
    tbl_JOIN_INNER_TD_2744_output.allocateHost();
    Table tbl_JOIN_INNER_TD_3948_output("tbl_JOIN_INNER_TD_3948_output", 377, 3, "");
    tbl_JOIN_INNER_TD_3948_output.allocateHost();
    Table tbl_Filter_TD_3910_output("tbl_Filter_TD_3910_output", 6100000, 1, "");
    tbl_Filter_TD_3910_output.allocateHost();
    Table tbl_JOIN_INNER_TD_4766_output("tbl_JOIN_INNER_TD_4766_output", 52212, 3, "");
    tbl_JOIN_INNER_TD_4766_output.allocateHost();
    Table tbl_Filter_TD_3426_output("tbl_Filter_TD_3426_output", 6100000, 1, "");
    tbl_Filter_TD_3426_output.allocateHost();
    Table tbl_SerializeFromObject_TD_5838_input;
    tbl_SerializeFromObject_TD_5838_input = Table("orders", orders_n, 2, in_dir);
    tbl_SerializeFromObject_TD_5838_input.addCol("o_orderkey", 4);
    tbl_SerializeFromObject_TD_5838_input.addCol("o_orderstatus", 4);
    tbl_SerializeFromObject_TD_5838_input.allocateHost();
    tbl_SerializeFromObject_TD_5838_input.loadHost();
    Table tbl_SerializeFromObject_TD_5343_input_stringRowIDSubstitute;
    tbl_SerializeFromObject_TD_5343_input_stringRowIDSubstitute = Table("supplier", supplier_n, 3, in_dir);
    tbl_SerializeFromObject_TD_5343_input_stringRowIDSubstitute.addCol("s_suppkey", 4);
    tbl_SerializeFromObject_TD_5343_input_stringRowIDSubstitute.addCol("s_name", 4, 1, 0);
    tbl_SerializeFromObject_TD_5343_input_stringRowIDSubstitute.addCol("s_nationkey", 4);
    tbl_SerializeFromObject_TD_5343_input_stringRowIDSubstitute.allocateHost();
    tbl_SerializeFromObject_TD_5343_input_stringRowIDSubstitute.loadHost();
    Table tbl_SerializeFromObject_TD_5343_input;
    tbl_SerializeFromObject_TD_5343_input = Table("supplier", supplier_n, 3, in_dir);
    tbl_SerializeFromObject_TD_5343_input.addCol("s_suppkey", 4);
    tbl_SerializeFromObject_TD_5343_input.addCol("s_name", TPCH_READ_S_NAME_LEN+1);
    tbl_SerializeFromObject_TD_5343_input.addCol("s_nationkey", 4);
    tbl_SerializeFromObject_TD_5343_input.allocateHost();
    tbl_SerializeFromObject_TD_5343_input.loadHost();
    Table tbl_JOIN_LEFTANTI_TD_5359_output("tbl_JOIN_LEFTANTI_TD_5359_output", 1375555, 2, "");
    tbl_JOIN_LEFTANTI_TD_5359_output.allocateHost();
    Table tbl_SerializeFromObject_TD_4156_input;
    tbl_SerializeFromObject_TD_4156_input = Table("nation", nation_n, 2, in_dir);
    tbl_SerializeFromObject_TD_4156_input.addCol("n_nationkey", 4);
    tbl_SerializeFromObject_TD_4156_input.addCol("n_name", TPCH_READ_NATION_LEN+1);
    tbl_SerializeFromObject_TD_4156_input.allocateHost();
    tbl_SerializeFromObject_TD_4156_input.loadHost();
    Table tbl_JOIN_LEFTSEMI_TD_6733_output("tbl_JOIN_LEFTSEMI_TD_6733_output", 2417632, 2, "");
    tbl_JOIN_LEFTSEMI_TD_6733_output.allocateHost();
    Table tbl_JOIN_LEFTSEMI_TD_7250_output("tbl_JOIN_LEFTSEMI_TD_7250_output", 2844584, 2, "");
    tbl_JOIN_LEFTSEMI_TD_7250_output.allocateHost();
    Table tbl_Filter_TD_7610_output("tbl_Filter_TD_7610_output", 6100000, 2, "");
    tbl_Filter_TD_7610_output.allocateHost();
    Table tbl_Filter_TD_8392_output("tbl_Filter_TD_8392_output", 6100000, 2, "");
    tbl_Filter_TD_8392_output.allocateHost();
    Table tbl_SerializeFromObject_TD_8961_input;
    tbl_SerializeFromObject_TD_8961_input = Table("lineitem", lineitem_n, 2, in_dir);
    tbl_SerializeFromObject_TD_8961_input.addCol("l_orderkey", 4);
    tbl_SerializeFromObject_TD_8961_input.addCol("l_suppkey", 4);
    tbl_SerializeFromObject_TD_8961_input.allocateHost();
    tbl_SerializeFromObject_TD_8961_input.loadHost();
    Table tbl_SerializeFromObject_TD_918_input;
    tbl_SerializeFromObject_TD_918_input = Table("lineitem", lineitem_n, 4, in_dir);
    tbl_SerializeFromObject_TD_918_input.addCol("l_orderkey", 4);
    tbl_SerializeFromObject_TD_918_input.addCol("l_suppkey", 4);
    tbl_SerializeFromObject_TD_918_input.addCol("l_receiptdate", 4);
    tbl_SerializeFromObject_TD_918_input.addCol("l_commitdate", 4);
    tbl_SerializeFromObject_TD_918_input.allocateHost();
    tbl_SerializeFromObject_TD_918_input.loadHost();
    // ********************** Allocate Device Buffer ******************** // 
    tbl_JOIN_INNER_TD_2744_output.allocateDevBuffer(context_h, 32);
    tbl_JOIN_INNER_TD_3948_output.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_3910_output.allocateDevBuffer(context_h, 32);
    tbl_JOIN_INNER_TD_4766_output.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_3426_output.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_5343_input_stringRowIDSubstitute.allocateDevBuffer(context_h, 32);
    tbl_JOIN_LEFTANTI_TD_5359_output.allocateDevBuffer(context_h, 32);
    tbl_JOIN_LEFTSEMI_TD_6733_output.allocateDevBuffer(context_h, 32);
    tbl_JOIN_LEFTSEMI_TD_7250_output.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_7610_output.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_8392_output.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_8961_input.allocateDevBuffer(context_h, 32);
    // ****************************** Config **************************** // 
    cfgCmd cfg_JOIN_INNER_TD_2744_cmds;
    cfg_JOIN_INNER_TD_2744_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_2744_gqe_join (cfg_JOIN_INNER_TD_2744_cmds.cmd);
    cfg_JOIN_INNER_TD_2744_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_INNER_TD_3948_cmds;
    cfg_JOIN_INNER_TD_3948_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_3948_gqe_join (cfg_JOIN_INNER_TD_3948_cmds.cmd);
    cfg_JOIN_INNER_TD_3948_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_INNER_TD_4766_cmds;
    cfg_JOIN_INNER_TD_4766_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_4766_gqe_join (cfg_JOIN_INNER_TD_4766_cmds.cmd);
    cfg_JOIN_INNER_TD_4766_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_LEFTANTI_TD_5359_cmds;
    cfg_JOIN_LEFTANTI_TD_5359_cmds.allocateHost();
    get_cfg_dat_JOIN_LEFTANTI_TD_5359_gqe_join (cfg_JOIN_LEFTANTI_TD_5359_cmds.cmd);
    cfg_JOIN_LEFTANTI_TD_5359_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_LEFTSEMI_TD_6733_cmds;
    cfg_JOIN_LEFTSEMI_TD_6733_cmds.allocateHost();
    get_cfg_dat_JOIN_LEFTSEMI_TD_6733_gqe_join (cfg_JOIN_LEFTSEMI_TD_6733_cmds.cmd);
    cfg_JOIN_LEFTSEMI_TD_6733_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_LEFTSEMI_TD_7250_cmds;
    cfg_JOIN_LEFTSEMI_TD_7250_cmds.allocateHost();
    get_cfg_dat_JOIN_LEFTSEMI_TD_7250_gqe_join (cfg_JOIN_LEFTSEMI_TD_7250_cmds.cmd);
    cfg_JOIN_LEFTSEMI_TD_7250_cmds.allocateDevBuffer(context_h, 32);
    // *************************** Kernel Setup ************************* // 
    bufferTmp buftmp_h(context_h); 
    buftmp_h.initBuffer(q_h); 
    std::cout << std::endl; 
    krnlEngine krnl_JOIN_INNER_TD_2744;
    krnl_JOIN_INNER_TD_2744 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_2744.setup(tbl_Filter_TD_3910_output, tbl_JOIN_INNER_TD_3948_output, tbl_JOIN_INNER_TD_2744_output, cfg_JOIN_INNER_TD_2744_cmds, buftmp_h);
    krnlEngine krnl_JOIN_INNER_TD_3948;
    krnl_JOIN_INNER_TD_3948 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_3948.setup(tbl_JOIN_INNER_TD_4766_output, tbl_Filter_TD_3426_output, tbl_JOIN_INNER_TD_3948_output, cfg_JOIN_INNER_TD_3948_cmds, buftmp_h);
    krnlEngine krnl_JOIN_INNER_TD_4766;
    krnl_JOIN_INNER_TD_4766 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_4766.setup(tbl_SerializeFromObject_TD_5343_input_stringRowIDSubstitute, tbl_JOIN_LEFTANTI_TD_5359_output, tbl_JOIN_INNER_TD_4766_output, cfg_JOIN_INNER_TD_4766_cmds, buftmp_h);
    krnlEngine krnl_JOIN_LEFTANTI_TD_5359;
    krnl_JOIN_LEFTANTI_TD_5359 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_LEFTANTI_TD_5359.setup(tbl_JOIN_LEFTSEMI_TD_6733_output, tbl_Filter_TD_7610_output, tbl_JOIN_LEFTANTI_TD_5359_output, cfg_JOIN_LEFTANTI_TD_5359_cmds, buftmp_h);
    krnlEngine krnl_JOIN_LEFTSEMI_TD_6733;
    krnl_JOIN_LEFTSEMI_TD_6733 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_LEFTSEMI_TD_6733.setup(tbl_Filter_TD_7610_output, tbl_JOIN_LEFTSEMI_TD_7250_output, tbl_JOIN_LEFTSEMI_TD_6733_output, cfg_JOIN_LEFTSEMI_TD_6733_cmds, buftmp_h);
    krnlEngine krnl_JOIN_LEFTSEMI_TD_7250;
    krnl_JOIN_LEFTSEMI_TD_7250 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_LEFTSEMI_TD_7250.setup(tbl_SerializeFromObject_TD_8961_input, tbl_Filter_TD_8392_output, tbl_JOIN_LEFTSEMI_TD_7250_output, cfg_JOIN_LEFTSEMI_TD_7250_cmds, buftmp_h);
    // ************************** Transfer Engine *********************** // 
    transEngine trans_JOIN_INNER_TD_2744;
    trans_JOIN_INNER_TD_2744.setq(q_h);
    trans_JOIN_INNER_TD_2744.add(&(cfg_JOIN_INNER_TD_2744_cmds));
    transEngine trans_JOIN_INNER_TD_2744_out;
    trans_JOIN_INNER_TD_2744_out.setq(q_h);
    q_h.finish();
    transEngine trans_JOIN_INNER_TD_3948;
    trans_JOIN_INNER_TD_3948.setq(q_h);
    trans_JOIN_INNER_TD_3948.add(&(cfg_JOIN_INNER_TD_3948_cmds));
    q_h.finish();
    transEngine trans_JOIN_INNER_TD_4766;
    trans_JOIN_INNER_TD_4766.setq(q_h);
    trans_JOIN_INNER_TD_4766.add(&(cfg_JOIN_INNER_TD_4766_cmds));
    trans_JOIN_INNER_TD_4766.add(&(tbl_SerializeFromObject_TD_5343_input_stringRowIDSubstitute));
    q_h.finish();
    transEngine trans_JOIN_LEFTANTI_TD_5359;
    trans_JOIN_LEFTANTI_TD_5359.setq(q_h);
    trans_JOIN_LEFTANTI_TD_5359.add(&(cfg_JOIN_LEFTANTI_TD_5359_cmds));
    q_h.finish();
    transEngine trans_JOIN_LEFTSEMI_TD_6733;
    trans_JOIN_LEFTSEMI_TD_6733.setq(q_h);
    trans_JOIN_LEFTSEMI_TD_6733.add(&(cfg_JOIN_LEFTSEMI_TD_6733_cmds));
    q_h.finish();
    transEngine trans_JOIN_LEFTSEMI_TD_7250;
    trans_JOIN_LEFTSEMI_TD_7250.setq(q_h);
    trans_JOIN_LEFTSEMI_TD_7250.add(&(cfg_JOIN_LEFTSEMI_TD_7250_cmds));
    trans_JOIN_LEFTSEMI_TD_7250.add(&(tbl_SerializeFromObject_TD_8961_input));
    q_h.finish();
    // ****************************** Events **************************** // 
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_2744;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_2744;
    std::vector<cl::Event> events_JOIN_INNER_TD_2744;
    events_h2d_wr_JOIN_INNER_TD_2744.resize(1);
    events_d2h_rd_JOIN_INNER_TD_2744.resize(1);
    events_JOIN_INNER_TD_2744.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_2744;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_2744;
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_3948;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_3948;
    std::vector<cl::Event> events_JOIN_INNER_TD_3948;
    events_h2d_wr_JOIN_INNER_TD_3948.resize(1);
    events_d2h_rd_JOIN_INNER_TD_3948.resize(1);
    events_JOIN_INNER_TD_3948.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_3948;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_3948;
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_4766;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_4766;
    std::vector<cl::Event> events_JOIN_INNER_TD_4766;
    events_h2d_wr_JOIN_INNER_TD_4766.resize(1);
    events_d2h_rd_JOIN_INNER_TD_4766.resize(1);
    events_JOIN_INNER_TD_4766.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_4766;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_4766;
    std::vector<cl::Event> events_h2d_wr_JOIN_LEFTANTI_TD_5359;
    std::vector<cl::Event> events_d2h_rd_JOIN_LEFTANTI_TD_5359;
    std::vector<cl::Event> events_JOIN_LEFTANTI_TD_5359;
    events_h2d_wr_JOIN_LEFTANTI_TD_5359.resize(1);
    events_d2h_rd_JOIN_LEFTANTI_TD_5359.resize(1);
    events_JOIN_LEFTANTI_TD_5359.resize(1);
    std::vector<cl::Event> events_grp_JOIN_LEFTANTI_TD_5359;
    std::vector<cl::Event> prev_events_grp_JOIN_LEFTANTI_TD_5359;
    std::vector<cl::Event> events_h2d_wr_JOIN_LEFTSEMI_TD_6733;
    std::vector<cl::Event> events_d2h_rd_JOIN_LEFTSEMI_TD_6733;
    std::vector<cl::Event> events_JOIN_LEFTSEMI_TD_6733;
    events_h2d_wr_JOIN_LEFTSEMI_TD_6733.resize(1);
    events_d2h_rd_JOIN_LEFTSEMI_TD_6733.resize(1);
    events_JOIN_LEFTSEMI_TD_6733.resize(1);
    std::vector<cl::Event> events_grp_JOIN_LEFTSEMI_TD_6733;
    std::vector<cl::Event> prev_events_grp_JOIN_LEFTSEMI_TD_6733;
    std::vector<cl::Event> events_h2d_wr_JOIN_LEFTSEMI_TD_7250;
    std::vector<cl::Event> events_d2h_rd_JOIN_LEFTSEMI_TD_7250;
    std::vector<cl::Event> events_JOIN_LEFTSEMI_TD_7250;
    events_h2d_wr_JOIN_LEFTSEMI_TD_7250.resize(1);
    events_d2h_rd_JOIN_LEFTSEMI_TD_7250.resize(1);
    events_JOIN_LEFTSEMI_TD_7250.resize(1);
    std::vector<cl::Event> events_grp_JOIN_LEFTSEMI_TD_7250;
    std::vector<cl::Event> prev_events_grp_JOIN_LEFTSEMI_TD_7250;
    // **************************** Operations ************************** // 
    struct timeval tv_r_s, tv_r_e; 
    gettimeofday(&tv_r_s, 0); 

    struct timeval tv_r_Filter_8_979_s, tv_r_Filter_8_979_e;
    gettimeofday(&tv_r_Filter_8_979_s, 0);
    SW_Filter_TD_8392(tbl_SerializeFromObject_TD_918_input, tbl_Filter_TD_8392_output);
    gettimeofday(&tv_r_Filter_8_979_e, 0);

    struct timeval tv_r_Filter_7_388_s, tv_r_Filter_7_388_e;
    gettimeofday(&tv_r_Filter_7_388_s, 0);
    SW_Filter_TD_7610(tbl_SerializeFromObject_TD_918_input, tbl_Filter_TD_7610_output);
    gettimeofday(&tv_r_Filter_7_388_e, 0);

    struct timeval tv_r_JOIN_LEFTSEMI_7_764_s, tv_r_JOIN_LEFTSEMI_7_764_e;
    gettimeofday(&tv_r_JOIN_LEFTSEMI_7_764_s, 0);
    trans_JOIN_LEFTSEMI_TD_7250.add(&(tbl_Filter_TD_8392_output));
    trans_JOIN_LEFTSEMI_TD_7250.host2dev(0, &(prev_events_grp_JOIN_LEFTSEMI_TD_7250), &(events_h2d_wr_JOIN_LEFTSEMI_TD_7250[0]));
    events_grp_JOIN_LEFTSEMI_TD_7250.push_back(events_h2d_wr_JOIN_LEFTSEMI_TD_7250[0]);
    krnl_JOIN_LEFTSEMI_TD_7250.run(0, &(events_grp_JOIN_LEFTSEMI_TD_7250), &(events_JOIN_LEFTSEMI_TD_7250[0]));
    gettimeofday(&tv_r_JOIN_LEFTSEMI_7_764_e, 0);

    struct timeval tv_r_JOIN_LEFTSEMI_6_809_s, tv_r_JOIN_LEFTSEMI_6_809_e;
    gettimeofday(&tv_r_JOIN_LEFTSEMI_6_809_s, 0);
    prev_events_grp_JOIN_LEFTSEMI_TD_6733.push_back(events_h2d_wr_JOIN_LEFTSEMI_TD_7250[0]);
    trans_JOIN_LEFTSEMI_TD_6733.add(&(tbl_Filter_TD_7610_output));
    trans_JOIN_LEFTSEMI_TD_6733.host2dev(0, &(prev_events_grp_JOIN_LEFTSEMI_TD_6733), &(events_h2d_wr_JOIN_LEFTSEMI_TD_6733[0]));
    events_grp_JOIN_LEFTSEMI_TD_6733.push_back(events_h2d_wr_JOIN_LEFTSEMI_TD_6733[0]);
    events_grp_JOIN_LEFTSEMI_TD_6733.push_back(events_JOIN_LEFTSEMI_TD_7250[0]);
    krnl_JOIN_LEFTSEMI_TD_6733.run(0, &(events_grp_JOIN_LEFTSEMI_TD_6733), &(events_JOIN_LEFTSEMI_TD_6733[0]));
    gettimeofday(&tv_r_JOIN_LEFTSEMI_6_809_e, 0);

    struct timeval tv_r_JOIN_LEFTANTI_5_467_s, tv_r_JOIN_LEFTANTI_5_467_e;
    gettimeofday(&tv_r_JOIN_LEFTANTI_5_467_s, 0);
    prev_events_grp_JOIN_LEFTANTI_TD_5359.push_back(events_h2d_wr_JOIN_LEFTSEMI_TD_6733[0]);
    trans_JOIN_LEFTANTI_TD_5359.add(&(tbl_Filter_TD_7610_output));
    trans_JOIN_LEFTANTI_TD_5359.host2dev(0, &(prev_events_grp_JOIN_LEFTANTI_TD_5359), &(events_h2d_wr_JOIN_LEFTANTI_TD_5359[0]));
    events_grp_JOIN_LEFTANTI_TD_5359.push_back(events_h2d_wr_JOIN_LEFTANTI_TD_5359[0]);
    events_grp_JOIN_LEFTANTI_TD_5359.push_back(events_JOIN_LEFTSEMI_TD_6733[0]);
    krnl_JOIN_LEFTANTI_TD_5359.run(0, &(events_grp_JOIN_LEFTANTI_TD_5359), &(events_JOIN_LEFTANTI_TD_5359[0]));
    gettimeofday(&tv_r_JOIN_LEFTANTI_5_467_e, 0);

    struct timeval tv_r_Filter_3_946_s, tv_r_Filter_3_946_e;
    gettimeofday(&tv_r_Filter_3_946_s, 0);
    SW_Filter_TD_3426(tbl_SerializeFromObject_TD_4156_input, tbl_Filter_TD_3426_output);
    gettimeofday(&tv_r_Filter_3_946_e, 0);

    struct timeval tv_r_JOIN_INNER_4_752_s, tv_r_JOIN_INNER_4_752_e;
    gettimeofday(&tv_r_JOIN_INNER_4_752_s, 0);
    prev_events_grp_JOIN_INNER_TD_4766.push_back(events_h2d_wr_JOIN_LEFTANTI_TD_5359[0]);
    trans_JOIN_INNER_TD_4766.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_4766), &(events_h2d_wr_JOIN_INNER_TD_4766[0]));
    events_grp_JOIN_INNER_TD_4766.push_back(events_h2d_wr_JOIN_INNER_TD_4766[0]);
    events_grp_JOIN_INNER_TD_4766.push_back(events_JOIN_LEFTANTI_TD_5359[0]);
    krnl_JOIN_INNER_TD_4766.run(0, &(events_grp_JOIN_INNER_TD_4766), &(events_JOIN_INNER_TD_4766[0]));
    gettimeofday(&tv_r_JOIN_INNER_4_752_e, 0);

    struct timeval tv_r_Filter_3_694_s, tv_r_Filter_3_694_e;
    gettimeofday(&tv_r_Filter_3_694_s, 0);
    SW_Filter_TD_3910(tbl_SerializeFromObject_TD_5838_input, tbl_Filter_TD_3910_output);
    gettimeofday(&tv_r_Filter_3_694_e, 0);

    struct timeval tv_r_JOIN_INNER_3_982_s, tv_r_JOIN_INNER_3_982_e;
    gettimeofday(&tv_r_JOIN_INNER_3_982_s, 0);
    prev_events_grp_JOIN_INNER_TD_3948.push_back(events_h2d_wr_JOIN_INNER_TD_4766[0]);
    trans_JOIN_INNER_TD_3948.add(&(tbl_Filter_TD_3426_output));
    trans_JOIN_INNER_TD_3948.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_3948), &(events_h2d_wr_JOIN_INNER_TD_3948[0]));
    events_grp_JOIN_INNER_TD_3948.push_back(events_h2d_wr_JOIN_INNER_TD_3948[0]);
    events_grp_JOIN_INNER_TD_3948.push_back(events_JOIN_INNER_TD_4766[0]);
    krnl_JOIN_INNER_TD_3948.run(0, &(events_grp_JOIN_INNER_TD_3948), &(events_JOIN_INNER_TD_3948[0]));
    gettimeofday(&tv_r_JOIN_INNER_3_982_e, 0);

    struct timeval tv_r_JOIN_INNER_2_522_s, tv_r_JOIN_INNER_2_522_e;
    gettimeofday(&tv_r_JOIN_INNER_2_522_s, 0);
    prev_events_grp_JOIN_INNER_TD_2744.push_back(events_h2d_wr_JOIN_INNER_TD_3948[0]);
    trans_JOIN_INNER_TD_2744.add(&(tbl_Filter_TD_3910_output));
    trans_JOIN_INNER_TD_2744.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_2744), &(events_h2d_wr_JOIN_INNER_TD_2744[0]));
    events_grp_JOIN_INNER_TD_2744.push_back(events_h2d_wr_JOIN_INNER_TD_2744[0]);
    events_grp_JOIN_INNER_TD_2744.push_back(events_JOIN_INNER_TD_3948[0]);
    krnl_JOIN_INNER_TD_2744.run(0, &(events_grp_JOIN_INNER_TD_2744), &(events_JOIN_INNER_TD_2744[0]));
    
    trans_JOIN_INNER_TD_2744_out.add(&(tbl_JOIN_INNER_TD_2744_output));
    trans_JOIN_INNER_TD_2744_out.dev2host(0, &(events_JOIN_INNER_TD_2744), &(events_d2h_rd_JOIN_INNER_TD_2744[0]));
    q_h.flush();
    q_h.finish();
    gettimeofday(&tv_r_JOIN_INNER_2_522_e, 0);

    struct timeval tv_r_Aggregate_1_383_s, tv_r_Aggregate_1_383_e;
    gettimeofday(&tv_r_Aggregate_1_383_s, 0);
    SW_Aggregate_TD_1459(tbl_JOIN_INNER_TD_2744_output, tbl_SerializeFromObject_TD_5343_input, tbl_SerializeFromObject_TD_4156_input, tbl_SerializeFromObject_TD_5838_input, tbl_Aggregate_TD_1459_output);
    gettimeofday(&tv_r_Aggregate_1_383_e, 0);

    struct timeval tv_r_Sort_0_297_s, tv_r_Sort_0_297_e;
    gettimeofday(&tv_r_Sort_0_297_s, 0);
    SW_Sort_TD_0339(tbl_Aggregate_TD_1459_output, tbl_Sort_TD_0339_output);
    gettimeofday(&tv_r_Sort_0_297_e, 0);

    gettimeofday(&tv_r_e, 0); 
    // **************************** Print Execution Time ************************** // 
    std::cout << "Filter_8: " << tvdiff(&tv_r_Filter_8_979_s, &tv_r_Filter_8_979_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_918_input: " << tbl_SerializeFromObject_TD_918_input.getNumRow() << " " << std::endl; 

    std::cout << "Filter_7: " << tvdiff(&tv_r_Filter_7_388_s, &tv_r_Filter_7_388_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_918_input: " << tbl_SerializeFromObject_TD_918_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_LEFTSEMI_7: " << tvdiff(&tv_r_JOIN_LEFTSEMI_7_764_s, &tv_r_JOIN_LEFTSEMI_7_764_e) / 1000.0 << " ms " 
     << "tbl_Filter_TD_8392_output: " << tbl_Filter_TD_8392_output.getNumRow() << " " << "tbl_SerializeFromObject_TD_8961_input: " << tbl_SerializeFromObject_TD_8961_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_LEFTSEMI_6: " << tvdiff(&tv_r_JOIN_LEFTSEMI_6_809_s, &tv_r_JOIN_LEFTSEMI_6_809_e) / 1000.0 << " ms " 
     << "tbl_JOIN_LEFTSEMI_TD_7250_output: " << tbl_JOIN_LEFTSEMI_TD_7250_output.getNumRow() << " " << "tbl_Filter_TD_7610_output: " << tbl_Filter_TD_7610_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_LEFTANTI_5: " << tvdiff(&tv_r_JOIN_LEFTANTI_5_467_s, &tv_r_JOIN_LEFTANTI_5_467_e) / 1000.0 << " ms " 
     << "tbl_Filter_TD_7610_output: " << tbl_Filter_TD_7610_output.getNumRow() << " " << "tbl_JOIN_LEFTSEMI_TD_6733_output: " << tbl_JOIN_LEFTSEMI_TD_6733_output.getNumRow() << " " << std::endl; 

    std::cout << "Filter_3: " << tvdiff(&tv_r_Filter_3_946_s, &tv_r_Filter_3_946_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_4156_input: " << tbl_SerializeFromObject_TD_4156_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_4: " << tvdiff(&tv_r_JOIN_INNER_4_752_s, &tv_r_JOIN_INNER_4_752_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_5343_input_stringRowIDSubstitute: " << tbl_SerializeFromObject_TD_5343_input_stringRowIDSubstitute.getNumRow() << " " << "tbl_JOIN_LEFTANTI_TD_5359_output: " << tbl_JOIN_LEFTANTI_TD_5359_output.getNumRow() << " " << std::endl; 

    std::cout << "Filter_3: " << tvdiff(&tv_r_Filter_3_694_s, &tv_r_Filter_3_694_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_5838_input: " << tbl_SerializeFromObject_TD_5838_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_3: " << tvdiff(&tv_r_JOIN_INNER_3_982_s, &tv_r_JOIN_INNER_3_982_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_4766_output: " << tbl_JOIN_INNER_TD_4766_output.getNumRow() << " " << "tbl_Filter_TD_3426_output: " << tbl_Filter_TD_3426_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_2: " << tvdiff(&tv_r_JOIN_INNER_2_522_s, &tv_r_JOIN_INNER_2_522_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_3948_output: " << tbl_JOIN_INNER_TD_3948_output.getNumRow() << " " << "tbl_Filter_TD_3910_output: " << tbl_Filter_TD_3910_output.getNumRow() << " " << std::endl; 

    std::cout << "Aggregate_1: " << tvdiff(&tv_r_Aggregate_1_383_s, &tv_r_Aggregate_1_383_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_2744_output: " << tbl_JOIN_INNER_TD_2744_output.getNumRow() << " " << std::endl; 

    std::cout << "Sort_0: " << tvdiff(&tv_r_Sort_0_297_s, &tv_r_Sort_0_297_e) / 1000.0 << " ms " 
     << "tbl_Aggregate_TD_1459_output: " << tbl_Aggregate_TD_1459_output.getNumRow() << " " << std::endl; 

    std::cout << std::endl << " Total execution time: " << tvdiff(&tv_r_s, &tv_r_e) / 1000 << " ms"; 

    std::cout << std::endl << " Spark elapsed time: " << 103.69742 * 1000 << "ms" << std::endl; 
    return 0; 
}
