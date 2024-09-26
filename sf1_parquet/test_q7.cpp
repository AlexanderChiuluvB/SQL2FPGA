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

#include "cfgFunc_q7.hpp" 
#include "q7.hpp" 

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
    std::cout << "NOTE:running query #7\n."; 
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
    Table tbl_Sort_TD_0417_output("tbl_Sort_TD_0417_output", 6100000, 4, "");
    tbl_Sort_TD_0417_output.allocateHost();
    Table tbl_Aggregate_TD_188_output("tbl_Aggregate_TD_188_output", 6100000, 4, "");
    tbl_Aggregate_TD_188_output.allocateHost();
    Table tbl_Project_TD_2726_output("tbl_Project_TD_2726_output", 6100000, 4, "");
    tbl_Project_TD_2726_output.allocateHost();
    Table tbl_JOIN_INNER_TD_397_output("tbl_JOIN_INNER_TD_397_output", 6100000, 6, "");
    tbl_JOIN_INNER_TD_397_output.allocateHost();
    Table tbl_JOIN_INNER_TD_4303_output("tbl_JOIN_INNER_TD_4303_output", 153500, 5, "");
    tbl_JOIN_INNER_TD_4303_output.allocateHost();
    Table tbl_Filter_TD_4739_output("tbl_Filter_TD_4739_output", 6100000, 2, "");
    tbl_Filter_TD_4739_output.allocateHost();
    Table tbl_JOIN_INNER_TD_5155_output("tbl_JOIN_INNER_TD_5155_output", 153500, 6, "");
    tbl_JOIN_INNER_TD_5155_output.allocateHost();
    Table tbl_SerializeFromObject_TD_5151_input;
    tbl_SerializeFromObject_TD_5151_input = Table("customer", customer_n, 2, in_dir);
    tbl_SerializeFromObject_TD_5151_input.addCol("c_custkey", 4);
    tbl_SerializeFromObject_TD_5151_input.addCol("c_nationkey", 4);
    tbl_SerializeFromObject_TD_5151_input.allocateHost();
    tbl_SerializeFromObject_TD_5151_input.loadHost();
    Table tbl_SerializeFromObject_TD_541_input;
    tbl_SerializeFromObject_TD_541_input = Table("nation", nation_n, 2, in_dir);
    tbl_SerializeFromObject_TD_541_input.addCol("n_nationkey", 4);
    tbl_SerializeFromObject_TD_541_input.addCol("n_name", TPCH_READ_NATION_LEN+1);
    tbl_SerializeFromObject_TD_541_input.allocateHost();
    tbl_SerializeFromObject_TD_541_input.loadHost();
    Table tbl_JOIN_INNER_TD_6929_output("tbl_JOIN_INNER_TD_6929_output", 153500, 6, "");
    tbl_JOIN_INNER_TD_6929_output.allocateHost();
    Table tbl_SerializeFromObject_TD_6542_input;
    tbl_SerializeFromObject_TD_6542_input = Table("orders", orders_n, 2, in_dir);
    tbl_SerializeFromObject_TD_6542_input.addCol("o_orderkey", 4);
    tbl_SerializeFromObject_TD_6542_input.addCol("o_custkey", 4);
    tbl_SerializeFromObject_TD_6542_input.allocateHost();
    tbl_SerializeFromObject_TD_6542_input.loadHost();
    Table tbl_JOIN_INNER_TD_7433_output("tbl_JOIN_INNER_TD_7433_output", 1829000, 5, "");
    tbl_JOIN_INNER_TD_7433_output.allocateHost();
    Table tbl_Filter_TD_5228_output("tbl_Filter_TD_5228_output", 6100000, 2, "");
    tbl_Filter_TD_5228_output.allocateHost();
    Table tbl_SerializeFromObject_TD_8423_input;
    tbl_SerializeFromObject_TD_8423_input = Table("supplier", supplier_n, 2, in_dir);
    tbl_SerializeFromObject_TD_8423_input.addCol("s_suppkey", 4);
    tbl_SerializeFromObject_TD_8423_input.addCol("s_nationkey", 4);
    tbl_SerializeFromObject_TD_8423_input.allocateHost();
    tbl_SerializeFromObject_TD_8423_input.loadHost();
    Table tbl_Filter_TD_8765_output("tbl_Filter_TD_8765_output", 6100000, 5, "");
    tbl_Filter_TD_8765_output.allocateHost();
    Table tbl_SerializeFromObject_TD_6439_input;
    tbl_SerializeFromObject_TD_6439_input = Table("nation", nation_n, 2, in_dir);
    tbl_SerializeFromObject_TD_6439_input.addCol("n_nationkey", 4);
    tbl_SerializeFromObject_TD_6439_input.addCol("n_name", TPCH_READ_NATION_LEN+1);
    tbl_SerializeFromObject_TD_6439_input.allocateHost();
    tbl_SerializeFromObject_TD_6439_input.loadHost();
    Table tbl_SerializeFromObject_TD_9451_input;
    tbl_SerializeFromObject_TD_9451_input = Table("lineitem", lineitem_n, 5, in_dir);
    tbl_SerializeFromObject_TD_9451_input.addCol("l_orderkey", 4);
    tbl_SerializeFromObject_TD_9451_input.addCol("l_suppkey", 4);
    tbl_SerializeFromObject_TD_9451_input.addCol("l_extendedprice", 4);
    tbl_SerializeFromObject_TD_9451_input.addCol("l_discount", 4);
    tbl_SerializeFromObject_TD_9451_input.addCol("l_shipdate", 4);
    tbl_SerializeFromObject_TD_9451_input.allocateHost();
    tbl_SerializeFromObject_TD_9451_input.loadHost();
    // ********************** Allocate Device Buffer ******************** // 
    tbl_JOIN_INNER_TD_4303_output.allocateDevBuffer(context_h, 32);
    tbl_JOIN_INNER_TD_5155_output.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_5151_input.allocateDevBuffer(context_h, 32);
    tbl_JOIN_INNER_TD_6929_output.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_6542_input.allocateDevBuffer(context_h, 32);
    tbl_JOIN_INNER_TD_7433_output.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_5228_output.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_8423_input.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_8765_output.allocateDevBuffer(context_h, 32);
    // ****************************** Config **************************** // 
    cfgCmd cfg_JOIN_INNER_TD_4303_cmds;
    cfg_JOIN_INNER_TD_4303_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_4303_gqe_join (cfg_JOIN_INNER_TD_4303_cmds.cmd);
    cfg_JOIN_INNER_TD_4303_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_INNER_TD_5155_cmds;
    cfg_JOIN_INNER_TD_5155_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_5155_gqe_join (cfg_JOIN_INNER_TD_5155_cmds.cmd);
    cfg_JOIN_INNER_TD_5155_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_INNER_TD_6929_cmds;
    cfg_JOIN_INNER_TD_6929_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_6929_gqe_join (cfg_JOIN_INNER_TD_6929_cmds.cmd);
    cfg_JOIN_INNER_TD_6929_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_INNER_TD_7433_cmds;
    cfg_JOIN_INNER_TD_7433_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_7433_gqe_join (cfg_JOIN_INNER_TD_7433_cmds.cmd);
    cfg_JOIN_INNER_TD_7433_cmds.allocateDevBuffer(context_h, 32);
    // *************************** Kernel Setup ************************* // 
    bufferTmp buftmp_h(context_h); 
    buftmp_h.initBuffer(q_h); 
    std::cout << std::endl; 
    krnlEngine krnl_JOIN_INNER_TD_4303;
    krnl_JOIN_INNER_TD_4303 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_4303.setup(tbl_SerializeFromObject_TD_5151_input, tbl_JOIN_INNER_TD_5155_output, tbl_JOIN_INNER_TD_4303_output, cfg_JOIN_INNER_TD_4303_cmds, buftmp_h);
    krnlEngine krnl_JOIN_INNER_TD_5155;
    krnl_JOIN_INNER_TD_5155 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_5155.setup(tbl_JOIN_INNER_TD_6929_output, tbl_SerializeFromObject_TD_6542_input, tbl_JOIN_INNER_TD_5155_output, cfg_JOIN_INNER_TD_5155_cmds, buftmp_h);
    krnlEngine krnl_JOIN_INNER_TD_6929;
    krnl_JOIN_INNER_TD_6929 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_6929.setup(tbl_Filter_TD_5228_output, tbl_JOIN_INNER_TD_7433_output, tbl_JOIN_INNER_TD_6929_output, cfg_JOIN_INNER_TD_6929_cmds, buftmp_h);
    krnlEngine krnl_JOIN_INNER_TD_7433;
    krnl_JOIN_INNER_TD_7433 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_7433.setup(tbl_SerializeFromObject_TD_8423_input, tbl_Filter_TD_8765_output, tbl_JOIN_INNER_TD_7433_output, cfg_JOIN_INNER_TD_7433_cmds, buftmp_h);
    // ************************** Transfer Engine *********************** // 
    transEngine trans_JOIN_INNER_TD_4303;
    trans_JOIN_INNER_TD_4303.setq(q_h);
    trans_JOIN_INNER_TD_4303.add(&(cfg_JOIN_INNER_TD_4303_cmds));
    trans_JOIN_INNER_TD_4303.add(&(tbl_SerializeFromObject_TD_5151_input));
    transEngine trans_JOIN_INNER_TD_4303_out;
    trans_JOIN_INNER_TD_4303_out.setq(q_h);
    q_h.finish();
    transEngine trans_JOIN_INNER_TD_5155;
    trans_JOIN_INNER_TD_5155.setq(q_h);
    trans_JOIN_INNER_TD_5155.add(&(cfg_JOIN_INNER_TD_5155_cmds));
    trans_JOIN_INNER_TD_5155.add(&(tbl_SerializeFromObject_TD_6542_input));
    q_h.finish();
    transEngine trans_JOIN_INNER_TD_6929;
    trans_JOIN_INNER_TD_6929.setq(q_h);
    trans_JOIN_INNER_TD_6929.add(&(cfg_JOIN_INNER_TD_6929_cmds));
    q_h.finish();
    transEngine trans_JOIN_INNER_TD_7433;
    trans_JOIN_INNER_TD_7433.setq(q_h);
    trans_JOIN_INNER_TD_7433.add(&(cfg_JOIN_INNER_TD_7433_cmds));
    trans_JOIN_INNER_TD_7433.add(&(tbl_SerializeFromObject_TD_8423_input));
    q_h.finish();
    // ****************************** Events **************************** // 
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_4303;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_4303;
    std::vector<cl::Event> events_JOIN_INNER_TD_4303;
    events_h2d_wr_JOIN_INNER_TD_4303.resize(1);
    events_d2h_rd_JOIN_INNER_TD_4303.resize(1);
    events_JOIN_INNER_TD_4303.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_4303;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_4303;
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_5155;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_5155;
    std::vector<cl::Event> events_JOIN_INNER_TD_5155;
    events_h2d_wr_JOIN_INNER_TD_5155.resize(1);
    events_d2h_rd_JOIN_INNER_TD_5155.resize(1);
    events_JOIN_INNER_TD_5155.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_5155;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_5155;
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_6929;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_6929;
    std::vector<cl::Event> events_JOIN_INNER_TD_6929;
    events_h2d_wr_JOIN_INNER_TD_6929.resize(1);
    events_d2h_rd_JOIN_INNER_TD_6929.resize(1);
    events_JOIN_INNER_TD_6929.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_6929;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_6929;
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_7433;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_7433;
    std::vector<cl::Event> events_JOIN_INNER_TD_7433;
    events_h2d_wr_JOIN_INNER_TD_7433.resize(1);
    events_d2h_rd_JOIN_INNER_TD_7433.resize(1);
    events_JOIN_INNER_TD_7433.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_7433;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_7433;
    // **************************** Operations ************************** // 
    struct timeval tv_r_s, tv_r_e; 
    gettimeofday(&tv_r_s, 0); 

    struct timeval tv_r_Filter_8_719_s, tv_r_Filter_8_719_e;
    gettimeofday(&tv_r_Filter_8_719_s, 0);
    SW_Filter_TD_8765(tbl_SerializeFromObject_TD_9451_input, tbl_Filter_TD_8765_output);
    gettimeofday(&tv_r_Filter_8_719_e, 0);

    struct timeval tv_r_Filter_5_426_s, tv_r_Filter_5_426_e;
    gettimeofday(&tv_r_Filter_5_426_s, 0);
    SW_Filter_TD_5228(tbl_SerializeFromObject_TD_6439_input, tbl_Filter_TD_5228_output);
    gettimeofday(&tv_r_Filter_5_426_e, 0);

    struct timeval tv_r_JOIN_INNER_7_185_s, tv_r_JOIN_INNER_7_185_e;
    gettimeofday(&tv_r_JOIN_INNER_7_185_s, 0);
    trans_JOIN_INNER_TD_7433.add(&(tbl_Filter_TD_8765_output));
    trans_JOIN_INNER_TD_7433.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_7433), &(events_h2d_wr_JOIN_INNER_TD_7433[0]));
    events_grp_JOIN_INNER_TD_7433.push_back(events_h2d_wr_JOIN_INNER_TD_7433[0]);
    krnl_JOIN_INNER_TD_7433.run(0, &(events_grp_JOIN_INNER_TD_7433), &(events_JOIN_INNER_TD_7433[0]));
    gettimeofday(&tv_r_JOIN_INNER_7_185_e, 0);

    struct timeval tv_r_JOIN_INNER_6_749_s, tv_r_JOIN_INNER_6_749_e;
    gettimeofday(&tv_r_JOIN_INNER_6_749_s, 0);
    prev_events_grp_JOIN_INNER_TD_6929.push_back(events_h2d_wr_JOIN_INNER_TD_7433[0]);
    trans_JOIN_INNER_TD_6929.add(&(tbl_Filter_TD_5228_output));
    trans_JOIN_INNER_TD_6929.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_6929), &(events_h2d_wr_JOIN_INNER_TD_6929[0]));
    events_grp_JOIN_INNER_TD_6929.push_back(events_h2d_wr_JOIN_INNER_TD_6929[0]);
    events_grp_JOIN_INNER_TD_6929.push_back(events_JOIN_INNER_TD_7433[0]);
    krnl_JOIN_INNER_TD_6929.run(0, &(events_grp_JOIN_INNER_TD_6929), &(events_JOIN_INNER_TD_6929[0]));
    gettimeofday(&tv_r_JOIN_INNER_6_749_e, 0);

    struct timeval tv_r_JOIN_INNER_5_379_s, tv_r_JOIN_INNER_5_379_e;
    gettimeofday(&tv_r_JOIN_INNER_5_379_s, 0);
    prev_events_grp_JOIN_INNER_TD_5155.push_back(events_h2d_wr_JOIN_INNER_TD_6929[0]);
    trans_JOIN_INNER_TD_5155.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_5155), &(events_h2d_wr_JOIN_INNER_TD_5155[0]));
    events_grp_JOIN_INNER_TD_5155.push_back(events_h2d_wr_JOIN_INNER_TD_5155[0]);
    events_grp_JOIN_INNER_TD_5155.push_back(events_JOIN_INNER_TD_6929[0]);
    krnl_JOIN_INNER_TD_5155.run(0, &(events_grp_JOIN_INNER_TD_5155), &(events_JOIN_INNER_TD_5155[0]));
    gettimeofday(&tv_r_JOIN_INNER_5_379_e, 0);

    struct timeval tv_r_Filter_4_395_s, tv_r_Filter_4_395_e;
    gettimeofday(&tv_r_Filter_4_395_s, 0);
    SW_Filter_TD_4739(tbl_SerializeFromObject_TD_541_input, tbl_Filter_TD_4739_output);
    gettimeofday(&tv_r_Filter_4_395_e, 0);

    struct timeval tv_r_JOIN_INNER_4_764_s, tv_r_JOIN_INNER_4_764_e;
    gettimeofday(&tv_r_JOIN_INNER_4_764_s, 0);
    prev_events_grp_JOIN_INNER_TD_4303.push_back(events_h2d_wr_JOIN_INNER_TD_5155[0]);
    trans_JOIN_INNER_TD_4303.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_4303), &(events_h2d_wr_JOIN_INNER_TD_4303[0]));
    events_grp_JOIN_INNER_TD_4303.push_back(events_h2d_wr_JOIN_INNER_TD_4303[0]);
    events_grp_JOIN_INNER_TD_4303.push_back(events_JOIN_INNER_TD_5155[0]);
    krnl_JOIN_INNER_TD_4303.run(0, &(events_grp_JOIN_INNER_TD_4303), &(events_JOIN_INNER_TD_4303[0]));
    
    trans_JOIN_INNER_TD_4303_out.add(&(tbl_JOIN_INNER_TD_4303_output));
    trans_JOIN_INNER_TD_4303_out.dev2host(0, &(events_JOIN_INNER_TD_4303), &(events_d2h_rd_JOIN_INNER_TD_4303[0]));
    q_h.flush();
    q_h.finish();
    gettimeofday(&tv_r_JOIN_INNER_4_764_e, 0);

    struct timeval tv_r_JOIN_INNER_3_658_s, tv_r_JOIN_INNER_3_658_e;
    gettimeofday(&tv_r_JOIN_INNER_3_658_s, 0);
    SW_JOIN_INNER_TD_397(tbl_JOIN_INNER_TD_4303_output, tbl_Filter_TD_4739_output, tbl_SerializeFromObject_TD_6439_input, tbl_JOIN_INNER_TD_397_output);
    gettimeofday(&tv_r_JOIN_INNER_3_658_e, 0);

    struct timeval tv_r_Project_2_429_s, tv_r_Project_2_429_e;
    gettimeofday(&tv_r_Project_2_429_s, 0);
    SW_Project_TD_2726(tbl_JOIN_INNER_TD_397_output, tbl_Project_TD_2726_output);
    gettimeofday(&tv_r_Project_2_429_e, 0);

    struct timeval tv_r_Aggregate_1_19_s, tv_r_Aggregate_1_19_e;
    gettimeofday(&tv_r_Aggregate_1_19_s, 0);
    SW_Aggregate_TD_188(tbl_Project_TD_2726_output, tbl_Aggregate_TD_188_output);
    gettimeofday(&tv_r_Aggregate_1_19_e, 0);

    struct timeval tv_r_Sort_0_809_s, tv_r_Sort_0_809_e;
    gettimeofday(&tv_r_Sort_0_809_s, 0);
    SW_Sort_TD_0417(tbl_Aggregate_TD_188_output, tbl_Sort_TD_0417_output);
    gettimeofday(&tv_r_Sort_0_809_e, 0);

    gettimeofday(&tv_r_e, 0); 
    // **************************** Print Execution Time ************************** // 
    std::cout << "Filter_8: " << tvdiff(&tv_r_Filter_8_719_s, &tv_r_Filter_8_719_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_9451_input: " << tbl_SerializeFromObject_TD_9451_input.getNumRow() << " " << std::endl; 

    std::cout << "Filter_5: " << tvdiff(&tv_r_Filter_5_426_s, &tv_r_Filter_5_426_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_6439_input: " << tbl_SerializeFromObject_TD_6439_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_7: " << tvdiff(&tv_r_JOIN_INNER_7_185_s, &tv_r_JOIN_INNER_7_185_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_8423_input: " << tbl_SerializeFromObject_TD_8423_input.getNumRow() << " " << "tbl_Filter_TD_8765_output: " << tbl_Filter_TD_8765_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_6: " << tvdiff(&tv_r_JOIN_INNER_6_749_s, &tv_r_JOIN_INNER_6_749_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_7433_output: " << tbl_JOIN_INNER_TD_7433_output.getNumRow() << " " << "tbl_Filter_TD_5228_output: " << tbl_Filter_TD_5228_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_5: " << tvdiff(&tv_r_JOIN_INNER_5_379_s, &tv_r_JOIN_INNER_5_379_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_6929_output: " << tbl_JOIN_INNER_TD_6929_output.getNumRow() << " " << "tbl_SerializeFromObject_TD_6542_input: " << tbl_SerializeFromObject_TD_6542_input.getNumRow() << " " << std::endl; 

    std::cout << "Filter_4: " << tvdiff(&tv_r_Filter_4_395_s, &tv_r_Filter_4_395_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_541_input: " << tbl_SerializeFromObject_TD_541_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_4: " << tvdiff(&tv_r_JOIN_INNER_4_764_s, &tv_r_JOIN_INNER_4_764_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_5155_output: " << tbl_JOIN_INNER_TD_5155_output.getNumRow() << " " << "tbl_SerializeFromObject_TD_5151_input: " << tbl_SerializeFromObject_TD_5151_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_3: " << tvdiff(&tv_r_JOIN_INNER_3_658_s, &tv_r_JOIN_INNER_3_658_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_4303_output: " << tbl_JOIN_INNER_TD_4303_output.getNumRow() << " " << "tbl_Filter_TD_4739_output: " << tbl_Filter_TD_4739_output.getNumRow() << " " << std::endl; 

    std::cout << "Project_2: " << tvdiff(&tv_r_Project_2_429_s, &tv_r_Project_2_429_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_397_output: " << tbl_JOIN_INNER_TD_397_output.getNumRow() << " " << std::endl; 

    std::cout << "Aggregate_1: " << tvdiff(&tv_r_Aggregate_1_19_s, &tv_r_Aggregate_1_19_e) / 1000.0 << " ms " 
     << "tbl_Project_TD_2726_output: " << tbl_Project_TD_2726_output.getNumRow() << " " << std::endl; 

    std::cout << "Sort_0: " << tvdiff(&tv_r_Sort_0_809_s, &tv_r_Sort_0_809_e) / 1000.0 << " ms " 
     << "tbl_Aggregate_TD_188_output: " << tbl_Aggregate_TD_188_output.getNumRow() << " " << std::endl; 

    std::cout << std::endl << " Total execution time: " << tvdiff(&tv_r_s, &tv_r_e) / 1000 << " ms"; 

    std::cout << std::endl << " Spark elapsed time: " << 59.788456 * 1000 << "ms" << std::endl; 
    return 0; 
}
