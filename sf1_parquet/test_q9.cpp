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

#include "cfgFunc_q9.hpp" 
#include "q9.hpp" 

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
    std::cout << "NOTE:running query #9\n."; 
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
    Table tbl_Sort_TD_0522_output("tbl_Sort_TD_0522_output", 6100000, 3, "");
    tbl_Sort_TD_0522_output.allocateHost();
    Table tbl_Aggregate_TD_1229_output("tbl_Aggregate_TD_1229_output", 6100000, 3, "");
    tbl_Aggregate_TD_1229_output.allocateHost();
    Table tbl_Project_TD_2468_output("tbl_Project_TD_2468_output", 6100000, 3, "");
    tbl_Project_TD_2468_output.allocateHost();
    Table tbl_JOIN_INNER_TD_3148_output("tbl_JOIN_INNER_TD_3148_output", 6100000, 6, "");
    tbl_JOIN_INNER_TD_3148_output.allocateHost();
    Table tbl_JOIN_INNER_TD_4762_output("tbl_JOIN_INNER_TD_4762_output", 319287, 6, "");
    tbl_JOIN_INNER_TD_4762_output.allocateHost();
    Table tbl_SerializeFromObject_TD_4825_input;
    tbl_SerializeFromObject_TD_4825_input = Table("nation", nation_n, 2, in_dir);
    tbl_SerializeFromObject_TD_4825_input.addCol("n_nationkey", 4);
    tbl_SerializeFromObject_TD_4825_input.addCol("n_name", TPCH_READ_NATION_LEN+1);
    tbl_SerializeFromObject_TD_4825_input.allocateHost();
    tbl_SerializeFromObject_TD_4825_input.loadHost();
    Table tbl_JOIN_INNER_TD_594_output("tbl_JOIN_INNER_TD_594_output", 319287, 6, "");
    tbl_JOIN_INNER_TD_594_output.allocateHost();
    Table tbl_SerializeFromObject_TD_5158_input;
    tbl_SerializeFromObject_TD_5158_input = Table("orders", orders_n, 2, in_dir);
    tbl_SerializeFromObject_TD_5158_input.addCol("o_orderkey", 4);
    tbl_SerializeFromObject_TD_5158_input.addCol("o_orderdate", 4);
    tbl_SerializeFromObject_TD_5158_input.allocateHost();
    tbl_SerializeFromObject_TD_5158_input.loadHost();
    Table tbl_JOIN_INNER_TD_6269_output("tbl_JOIN_INNER_TD_6269_output", 319287, 7, "");
    tbl_JOIN_INNER_TD_6269_output.allocateHost();
    Table tbl_SerializeFromObject_TD_6947_input;
    tbl_SerializeFromObject_TD_6947_input = Table("partsupp", partsupp_n, 3, in_dir);
    tbl_SerializeFromObject_TD_6947_input.addCol("ps_partkey", 4);
    tbl_SerializeFromObject_TD_6947_input.addCol("ps_suppkey", 4);
    tbl_SerializeFromObject_TD_6947_input.addCol("ps_supplycost", 4);
    tbl_SerializeFromObject_TD_6947_input.allocateHost();
    tbl_SerializeFromObject_TD_6947_input.loadHost();
    Table tbl_JOIN_INNER_TD_7502_output("tbl_JOIN_INNER_TD_7502_output", 319287, 6, "");
    tbl_JOIN_INNER_TD_7502_output.allocateHost();
    Table tbl_SerializeFromObject_TD_7663_input;
    tbl_SerializeFromObject_TD_7663_input = Table("supplier", supplier_n, 2, in_dir);
    tbl_SerializeFromObject_TD_7663_input.addCol("s_suppkey", 4);
    tbl_SerializeFromObject_TD_7663_input.addCol("s_nationkey", 4);
    tbl_SerializeFromObject_TD_7663_input.allocateHost();
    tbl_SerializeFromObject_TD_7663_input.loadHost();
    Table tbl_Filter_TD_8914_output("tbl_Filter_TD_8914_output", 6100000, 1, "");
    tbl_Filter_TD_8914_output.allocateHost();
    Table tbl_SerializeFromObject_TD_8692_input;
    tbl_SerializeFromObject_TD_8692_input = Table("lineitem", lineitem_n, 6, in_dir);
    tbl_SerializeFromObject_TD_8692_input.addCol("l_orderkey", 4);
    tbl_SerializeFromObject_TD_8692_input.addCol("l_partkey", 4);
    tbl_SerializeFromObject_TD_8692_input.addCol("l_suppkey", 4);
    tbl_SerializeFromObject_TD_8692_input.addCol("l_quantity", 4);
    tbl_SerializeFromObject_TD_8692_input.addCol("l_extendedprice", 4);
    tbl_SerializeFromObject_TD_8692_input.addCol("l_discount", 4);
    tbl_SerializeFromObject_TD_8692_input.allocateHost();
    tbl_SerializeFromObject_TD_8692_input.loadHost();
    Table tbl_SerializeFromObject_TD_9157_input;
    tbl_SerializeFromObject_TD_9157_input = Table("part", part_n, 2, in_dir);
    tbl_SerializeFromObject_TD_9157_input.addCol("p_partkey", 4);
    tbl_SerializeFromObject_TD_9157_input.addCol("p_name", TPCH_READ_P_NAME_LEN+1);
    tbl_SerializeFromObject_TD_9157_input.allocateHost();
    tbl_SerializeFromObject_TD_9157_input.loadHost();
    // ********************** Allocate Device Buffer ******************** // 
    tbl_JOIN_INNER_TD_4762_output.allocateDevBuffer(context_h, 32);
    tbl_JOIN_INNER_TD_594_output.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_5158_input.allocateDevBuffer(context_h, 32);
    tbl_JOIN_INNER_TD_6269_output.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_6947_input.allocateDevBuffer(context_h, 32);
    tbl_JOIN_INNER_TD_7502_output.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_7663_input.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_8914_output.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_8692_input.allocateDevBuffer(context_h, 32);
    // ****************************** Config **************************** // 
    cfgCmd cfg_JOIN_INNER_TD_4762_cmds;
    cfg_JOIN_INNER_TD_4762_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_4762_gqe_join (cfg_JOIN_INNER_TD_4762_cmds.cmd);
    cfg_JOIN_INNER_TD_4762_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_INNER_TD_594_cmds;
    cfg_JOIN_INNER_TD_594_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_594_gqe_join (cfg_JOIN_INNER_TD_594_cmds.cmd);
    cfg_JOIN_INNER_TD_594_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_INNER_TD_6269_cmds;
    cfg_JOIN_INNER_TD_6269_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_6269_gqe_join (cfg_JOIN_INNER_TD_6269_cmds.cmd);
    cfg_JOIN_INNER_TD_6269_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_INNER_TD_7502_cmds;
    cfg_JOIN_INNER_TD_7502_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_7502_gqe_join (cfg_JOIN_INNER_TD_7502_cmds.cmd);
    cfg_JOIN_INNER_TD_7502_cmds.allocateDevBuffer(context_h, 32);
    // *************************** Kernel Setup ************************* // 
    bufferTmp buftmp_h(context_h); 
    buftmp_h.initBuffer(q_h); 
    std::cout << std::endl; 
    krnlEngine krnl_JOIN_INNER_TD_4762;
    krnl_JOIN_INNER_TD_4762 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_4762.setup(tbl_JOIN_INNER_TD_594_output, tbl_SerializeFromObject_TD_5158_input, tbl_JOIN_INNER_TD_4762_output, cfg_JOIN_INNER_TD_4762_cmds, buftmp_h);
    krnlEngine krnl_JOIN_INNER_TD_594;
    krnl_JOIN_INNER_TD_594 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_594.setup(tbl_JOIN_INNER_TD_6269_output, tbl_SerializeFromObject_TD_6947_input, tbl_JOIN_INNER_TD_594_output, cfg_JOIN_INNER_TD_594_cmds, buftmp_h);
    krnlEngine krnl_JOIN_INNER_TD_6269;
    krnl_JOIN_INNER_TD_6269 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_6269.setup(tbl_SerializeFromObject_TD_7663_input, tbl_JOIN_INNER_TD_7502_output, tbl_JOIN_INNER_TD_6269_output, cfg_JOIN_INNER_TD_6269_cmds, buftmp_h);
    krnlEngine krnl_JOIN_INNER_TD_7502;
    krnl_JOIN_INNER_TD_7502 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_7502.setup(tbl_Filter_TD_8914_output, tbl_SerializeFromObject_TD_8692_input, tbl_JOIN_INNER_TD_7502_output, cfg_JOIN_INNER_TD_7502_cmds, buftmp_h);
    // ************************** Transfer Engine *********************** // 
    transEngine trans_JOIN_INNER_TD_4762;
    trans_JOIN_INNER_TD_4762.setq(q_h);
    trans_JOIN_INNER_TD_4762.add(&(cfg_JOIN_INNER_TD_4762_cmds));
    trans_JOIN_INNER_TD_4762.add(&(tbl_SerializeFromObject_TD_5158_input));
    transEngine trans_JOIN_INNER_TD_4762_out;
    trans_JOIN_INNER_TD_4762_out.setq(q_h);
    q_h.finish();
    transEngine trans_JOIN_INNER_TD_594;
    trans_JOIN_INNER_TD_594.setq(q_h);
    trans_JOIN_INNER_TD_594.add(&(cfg_JOIN_INNER_TD_594_cmds));
    trans_JOIN_INNER_TD_594.add(&(tbl_SerializeFromObject_TD_6947_input));
    q_h.finish();
    transEngine trans_JOIN_INNER_TD_6269;
    trans_JOIN_INNER_TD_6269.setq(q_h);
    trans_JOIN_INNER_TD_6269.add(&(cfg_JOIN_INNER_TD_6269_cmds));
    trans_JOIN_INNER_TD_6269.add(&(tbl_SerializeFromObject_TD_7663_input));
    q_h.finish();
    transEngine trans_JOIN_INNER_TD_7502;
    trans_JOIN_INNER_TD_7502.setq(q_h);
    trans_JOIN_INNER_TD_7502.add(&(cfg_JOIN_INNER_TD_7502_cmds));
    trans_JOIN_INNER_TD_7502.add(&(tbl_SerializeFromObject_TD_8692_input));
    q_h.finish();
    // ****************************** Events **************************** // 
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_4762;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_4762;
    std::vector<cl::Event> events_JOIN_INNER_TD_4762;
    events_h2d_wr_JOIN_INNER_TD_4762.resize(1);
    events_d2h_rd_JOIN_INNER_TD_4762.resize(1);
    events_JOIN_INNER_TD_4762.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_4762;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_4762;
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_594;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_594;
    std::vector<cl::Event> events_JOIN_INNER_TD_594;
    events_h2d_wr_JOIN_INNER_TD_594.resize(1);
    events_d2h_rd_JOIN_INNER_TD_594.resize(1);
    events_JOIN_INNER_TD_594.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_594;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_594;
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_6269;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_6269;
    std::vector<cl::Event> events_JOIN_INNER_TD_6269;
    events_h2d_wr_JOIN_INNER_TD_6269.resize(1);
    events_d2h_rd_JOIN_INNER_TD_6269.resize(1);
    events_JOIN_INNER_TD_6269.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_6269;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_6269;
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_7502;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_7502;
    std::vector<cl::Event> events_JOIN_INNER_TD_7502;
    events_h2d_wr_JOIN_INNER_TD_7502.resize(1);
    events_d2h_rd_JOIN_INNER_TD_7502.resize(1);
    events_JOIN_INNER_TD_7502.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_7502;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_7502;
    // **************************** Operations ************************** // 
    struct timeval tv_r_s, tv_r_e; 
    gettimeofday(&tv_r_s, 0); 

    struct timeval tv_r_Filter_8_981_s, tv_r_Filter_8_981_e;
    gettimeofday(&tv_r_Filter_8_981_s, 0);
    SW_Filter_TD_8914(tbl_SerializeFromObject_TD_9157_input, tbl_Filter_TD_8914_output);
    gettimeofday(&tv_r_Filter_8_981_e, 0);

    struct timeval tv_r_JOIN_INNER_7_177_s, tv_r_JOIN_INNER_7_177_e;
    gettimeofday(&tv_r_JOIN_INNER_7_177_s, 0);
    trans_JOIN_INNER_TD_7502.add(&(tbl_Filter_TD_8914_output));
    trans_JOIN_INNER_TD_7502.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_7502), &(events_h2d_wr_JOIN_INNER_TD_7502[0]));
    events_grp_JOIN_INNER_TD_7502.push_back(events_h2d_wr_JOIN_INNER_TD_7502[0]);
    krnl_JOIN_INNER_TD_7502.run(0, &(events_grp_JOIN_INNER_TD_7502), &(events_JOIN_INNER_TD_7502[0]));
    gettimeofday(&tv_r_JOIN_INNER_7_177_e, 0);

    struct timeval tv_r_JOIN_INNER_6_134_s, tv_r_JOIN_INNER_6_134_e;
    gettimeofday(&tv_r_JOIN_INNER_6_134_s, 0);
    prev_events_grp_JOIN_INNER_TD_6269.push_back(events_h2d_wr_JOIN_INNER_TD_7502[0]);
    trans_JOIN_INNER_TD_6269.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_6269), &(events_h2d_wr_JOIN_INNER_TD_6269[0]));
    events_grp_JOIN_INNER_TD_6269.push_back(events_h2d_wr_JOIN_INNER_TD_6269[0]);
    events_grp_JOIN_INNER_TD_6269.push_back(events_JOIN_INNER_TD_7502[0]);
    krnl_JOIN_INNER_TD_6269.run(0, &(events_grp_JOIN_INNER_TD_6269), &(events_JOIN_INNER_TD_6269[0]));
    gettimeofday(&tv_r_JOIN_INNER_6_134_e, 0);

    struct timeval tv_r_JOIN_INNER_5_240_s, tv_r_JOIN_INNER_5_240_e;
    gettimeofday(&tv_r_JOIN_INNER_5_240_s, 0);
    prev_events_grp_JOIN_INNER_TD_594.push_back(events_h2d_wr_JOIN_INNER_TD_6269[0]);
    trans_JOIN_INNER_TD_594.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_594), &(events_h2d_wr_JOIN_INNER_TD_594[0]));
    events_grp_JOIN_INNER_TD_594.push_back(events_h2d_wr_JOIN_INNER_TD_594[0]);
    events_grp_JOIN_INNER_TD_594.push_back(events_JOIN_INNER_TD_6269[0]);
    krnl_JOIN_INNER_TD_594.run(0, &(events_grp_JOIN_INNER_TD_594), &(events_JOIN_INNER_TD_594[0]));
    gettimeofday(&tv_r_JOIN_INNER_5_240_e, 0);

    struct timeval tv_r_JOIN_INNER_4_561_s, tv_r_JOIN_INNER_4_561_e;
    gettimeofday(&tv_r_JOIN_INNER_4_561_s, 0);
    prev_events_grp_JOIN_INNER_TD_4762.push_back(events_h2d_wr_JOIN_INNER_TD_594[0]);
    trans_JOIN_INNER_TD_4762.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_4762), &(events_h2d_wr_JOIN_INNER_TD_4762[0]));
    events_grp_JOIN_INNER_TD_4762.push_back(events_h2d_wr_JOIN_INNER_TD_4762[0]);
    events_grp_JOIN_INNER_TD_4762.push_back(events_JOIN_INNER_TD_594[0]);
    krnl_JOIN_INNER_TD_4762.run(0, &(events_grp_JOIN_INNER_TD_4762), &(events_JOIN_INNER_TD_4762[0]));
    
    trans_JOIN_INNER_TD_4762_out.add(&(tbl_JOIN_INNER_TD_4762_output));
    trans_JOIN_INNER_TD_4762_out.dev2host(0, &(events_JOIN_INNER_TD_4762), &(events_d2h_rd_JOIN_INNER_TD_4762[0]));
    q_h.flush();
    q_h.finish();
    gettimeofday(&tv_r_JOIN_INNER_4_561_e, 0);

    struct timeval tv_r_JOIN_INNER_3_245_s, tv_r_JOIN_INNER_3_245_e;
    gettimeofday(&tv_r_JOIN_INNER_3_245_s, 0);
    SW_JOIN_INNER_TD_3148(tbl_JOIN_INNER_TD_4762_output, tbl_SerializeFromObject_TD_4825_input, tbl_JOIN_INNER_TD_3148_output);
    gettimeofday(&tv_r_JOIN_INNER_3_245_e, 0);

    struct timeval tv_r_Project_2_830_s, tv_r_Project_2_830_e;
    gettimeofday(&tv_r_Project_2_830_s, 0);
    SW_Project_TD_2468(tbl_JOIN_INNER_TD_3148_output, tbl_Project_TD_2468_output);
    gettimeofday(&tv_r_Project_2_830_e, 0);

    struct timeval tv_r_Aggregate_1_549_s, tv_r_Aggregate_1_549_e;
    gettimeofday(&tv_r_Aggregate_1_549_s, 0);
    SW_Aggregate_TD_1229(tbl_Project_TD_2468_output, tbl_Aggregate_TD_1229_output);
    gettimeofday(&tv_r_Aggregate_1_549_e, 0);

    struct timeval tv_r_Sort_0_172_s, tv_r_Sort_0_172_e;
    gettimeofday(&tv_r_Sort_0_172_s, 0);
    SW_Sort_TD_0522(tbl_Aggregate_TD_1229_output, tbl_Sort_TD_0522_output);
    gettimeofday(&tv_r_Sort_0_172_e, 0);

    gettimeofday(&tv_r_e, 0); 
    // **************************** Print Execution Time ************************** // 
    std::cout << "Filter_8: " << tvdiff(&tv_r_Filter_8_981_s, &tv_r_Filter_8_981_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_9157_input: " << tbl_SerializeFromObject_TD_9157_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_7: " << tvdiff(&tv_r_JOIN_INNER_7_177_s, &tv_r_JOIN_INNER_7_177_e) / 1000.0 << " ms " 
     << "tbl_Filter_TD_8914_output: " << tbl_Filter_TD_8914_output.getNumRow() << " " << "tbl_SerializeFromObject_TD_8692_input: " << tbl_SerializeFromObject_TD_8692_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_6: " << tvdiff(&tv_r_JOIN_INNER_6_134_s, &tv_r_JOIN_INNER_6_134_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_7502_output: " << tbl_JOIN_INNER_TD_7502_output.getNumRow() << " " << "tbl_SerializeFromObject_TD_7663_input: " << tbl_SerializeFromObject_TD_7663_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_5: " << tvdiff(&tv_r_JOIN_INNER_5_240_s, &tv_r_JOIN_INNER_5_240_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_6269_output: " << tbl_JOIN_INNER_TD_6269_output.getNumRow() << " " << "tbl_SerializeFromObject_TD_6947_input: " << tbl_SerializeFromObject_TD_6947_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_4: " << tvdiff(&tv_r_JOIN_INNER_4_561_s, &tv_r_JOIN_INNER_4_561_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_594_output: " << tbl_JOIN_INNER_TD_594_output.getNumRow() << " " << "tbl_SerializeFromObject_TD_5158_input: " << tbl_SerializeFromObject_TD_5158_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_3: " << tvdiff(&tv_r_JOIN_INNER_3_245_s, &tv_r_JOIN_INNER_3_245_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_4762_output: " << tbl_JOIN_INNER_TD_4762_output.getNumRow() << " " << "tbl_SerializeFromObject_TD_4825_input: " << tbl_SerializeFromObject_TD_4825_input.getNumRow() << " " << std::endl; 

    std::cout << "Project_2: " << tvdiff(&tv_r_Project_2_830_s, &tv_r_Project_2_830_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_3148_output: " << tbl_JOIN_INNER_TD_3148_output.getNumRow() << " " << std::endl; 

    std::cout << "Aggregate_1: " << tvdiff(&tv_r_Aggregate_1_549_s, &tv_r_Aggregate_1_549_e) / 1000.0 << " ms " 
     << "tbl_Project_TD_2468_output: " << tbl_Project_TD_2468_output.getNumRow() << " " << std::endl; 

    std::cout << "Sort_0: " << tvdiff(&tv_r_Sort_0_172_s, &tv_r_Sort_0_172_e) / 1000.0 << " ms " 
     << "tbl_Aggregate_TD_1229_output: " << tbl_Aggregate_TD_1229_output.getNumRow() << " " << std::endl; 

    std::cout << std::endl << " Total execution time: " << tvdiff(&tv_r_s, &tv_r_e) / 1000 << " ms"; 

    std::cout << std::endl << " Spark elapsed time: " << 40.27751 * 1000 << "ms" << std::endl; 
    return 0; 
}
