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

#include "cfgFunc_q5.hpp" 
#include "q5.hpp" 

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
    std::cout << "NOTE:running query #5\n."; 
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
    Table tbl_Sort_TD_0669_output("tbl_Sort_TD_0669_output", 6100000, 2, "");
    tbl_Sort_TD_0669_output.allocateHost();
    Table tbl_Aggregate_TD_1875_output("tbl_Aggregate_TD_1875_output", 6100000, 2, "");
    tbl_Aggregate_TD_1875_output.allocateHost();
    Table tbl_JOIN_INNER_TD_2962_output("tbl_JOIN_INNER_TD_2962_output", 6100000, 3, "");
    tbl_JOIN_INNER_TD_2962_output.allocateHost();
    Table tbl_JOIN_INNER_TD_3474_output("tbl_JOIN_INNER_TD_3474_output", 6100000, 4, "");
    tbl_JOIN_INNER_TD_3474_output.allocateHost();
    Table tbl_Filter_TD_3828_output("tbl_Filter_TD_3828_output", 6100000, 1, "");
    tbl_Filter_TD_3828_output.allocateHost();
    Table tbl_JOIN_INNER_TD_451_output("tbl_JOIN_INNER_TD_451_output", 37000, 3, "");
    tbl_JOIN_INNER_TD_451_output.allocateHost();
    Table tbl_SerializeFromObject_TD_4481_input;
    tbl_SerializeFromObject_TD_4481_input = Table("nation", nation_n, 3, in_dir);
    tbl_SerializeFromObject_TD_4481_input.addCol("n_nationkey", 4);
    tbl_SerializeFromObject_TD_4481_input.addCol("n_name", TPCH_READ_NATION_LEN+1);
    tbl_SerializeFromObject_TD_4481_input.addCol("n_regionkey", 4);
    tbl_SerializeFromObject_TD_4481_input.allocateHost();
    tbl_SerializeFromObject_TD_4481_input.loadHost();
    Table tbl_SerializeFromObject_TD_4773_input;
    tbl_SerializeFromObject_TD_4773_input = Table("region", region_n, 2, in_dir);
    tbl_SerializeFromObject_TD_4773_input.addCol("r_regionkey", 4);
    tbl_SerializeFromObject_TD_4773_input.addCol("r_name", TPCH_READ_REGION_LEN+1);
    tbl_SerializeFromObject_TD_4773_input.allocateHost();
    tbl_SerializeFromObject_TD_4773_input.loadHost();
    Table tbl_JOIN_INNER_TD_5581_output("tbl_JOIN_INNER_TD_5581_output", 909000, 4, "");
    tbl_JOIN_INNER_TD_5581_output.allocateHost();
    Table tbl_SerializeFromObject_TD_5598_input;
    tbl_SerializeFromObject_TD_5598_input = Table("supplier", supplier_n, 2, in_dir);
    tbl_SerializeFromObject_TD_5598_input.addCol("s_suppkey", 4);
    tbl_SerializeFromObject_TD_5598_input.addCol("s_nationkey", 4);
    tbl_SerializeFromObject_TD_5598_input.allocateHost();
    tbl_SerializeFromObject_TD_5598_input.loadHost();
    Table tbl_JOIN_INNER_TD_6771_output("tbl_JOIN_INNER_TD_6771_output", 227000, 2, "");
    tbl_JOIN_INNER_TD_6771_output.allocateHost();
    Table tbl_SerializeFromObject_TD_6952_input;
    tbl_SerializeFromObject_TD_6952_input = Table("lineitem", lineitem_n, 4, in_dir);
    tbl_SerializeFromObject_TD_6952_input.addCol("l_orderkey", 4);
    tbl_SerializeFromObject_TD_6952_input.addCol("l_suppkey", 4);
    tbl_SerializeFromObject_TD_6952_input.addCol("l_extendedprice", 4);
    tbl_SerializeFromObject_TD_6952_input.addCol("l_discount", 4);
    tbl_SerializeFromObject_TD_6952_input.allocateHost();
    tbl_SerializeFromObject_TD_6952_input.loadHost();
    Table tbl_SerializeFromObject_TD_7272_input;
    tbl_SerializeFromObject_TD_7272_input = Table("customer", customer_n, 2, in_dir);
    tbl_SerializeFromObject_TD_7272_input.addCol("c_custkey", 4);
    tbl_SerializeFromObject_TD_7272_input.addCol("c_nationkey", 4);
    tbl_SerializeFromObject_TD_7272_input.allocateHost();
    tbl_SerializeFromObject_TD_7272_input.loadHost();
    Table tbl_Filter_TD_7659_output("tbl_Filter_TD_7659_output", 6100000, 2, "");
    tbl_Filter_TD_7659_output.allocateHost();
    Table tbl_SerializeFromObject_TD_8531_input;
    tbl_SerializeFromObject_TD_8531_input = Table("orders", orders_n, 3, in_dir);
    tbl_SerializeFromObject_TD_8531_input.addCol("o_orderkey", 4);
    tbl_SerializeFromObject_TD_8531_input.addCol("o_custkey", 4);
    tbl_SerializeFromObject_TD_8531_input.addCol("o_orderdate", 4);
    tbl_SerializeFromObject_TD_8531_input.allocateHost();
    tbl_SerializeFromObject_TD_8531_input.loadHost();
    // ********************** Allocate Device Buffer ******************** // 
    tbl_JOIN_INNER_TD_451_output.allocateDevBuffer(context_h, 32);
    tbl_JOIN_INNER_TD_5581_output.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_5598_input.allocateDevBuffer(context_h, 32);
    tbl_JOIN_INNER_TD_6771_output.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_6952_input.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_7272_input.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_7659_output.allocateDevBuffer(context_h, 32);
    // ****************************** Config **************************** // 
    cfgCmd cfg_JOIN_INNER_TD_451_cmds;
    cfg_JOIN_INNER_TD_451_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_451_gqe_join (cfg_JOIN_INNER_TD_451_cmds.cmd);
    cfg_JOIN_INNER_TD_451_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_INNER_TD_5581_cmds;
    cfg_JOIN_INNER_TD_5581_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_5581_gqe_join (cfg_JOIN_INNER_TD_5581_cmds.cmd);
    cfg_JOIN_INNER_TD_5581_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_INNER_TD_6771_cmds;
    cfg_JOIN_INNER_TD_6771_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_6771_gqe_join (cfg_JOIN_INNER_TD_6771_cmds.cmd);
    cfg_JOIN_INNER_TD_6771_cmds.allocateDevBuffer(context_h, 32);
    // *************************** Kernel Setup ************************* // 
    bufferTmp buftmp_h(context_h); 
    buftmp_h.initBuffer(q_h); 
    std::cout << std::endl; 
    krnlEngine krnl_JOIN_INNER_TD_451;
    krnl_JOIN_INNER_TD_451 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_451.setup(tbl_SerializeFromObject_TD_5598_input, tbl_JOIN_INNER_TD_5581_output, tbl_JOIN_INNER_TD_451_output, cfg_JOIN_INNER_TD_451_cmds, buftmp_h);
    krnlEngine krnl_JOIN_INNER_TD_5581;
    krnl_JOIN_INNER_TD_5581 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_5581.setup(tbl_JOIN_INNER_TD_6771_output, tbl_SerializeFromObject_TD_6952_input, tbl_JOIN_INNER_TD_5581_output, cfg_JOIN_INNER_TD_5581_cmds, buftmp_h);
    krnlEngine krnl_JOIN_INNER_TD_6771;
    krnl_JOIN_INNER_TD_6771 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_6771.setup(tbl_SerializeFromObject_TD_7272_input, tbl_Filter_TD_7659_output, tbl_JOIN_INNER_TD_6771_output, cfg_JOIN_INNER_TD_6771_cmds, buftmp_h);
    // ************************** Transfer Engine *********************** // 
    transEngine trans_JOIN_INNER_TD_451;
    trans_JOIN_INNER_TD_451.setq(q_h);
    trans_JOIN_INNER_TD_451.add(&(cfg_JOIN_INNER_TD_451_cmds));
    trans_JOIN_INNER_TD_451.add(&(tbl_SerializeFromObject_TD_5598_input));
    transEngine trans_JOIN_INNER_TD_451_out;
    trans_JOIN_INNER_TD_451_out.setq(q_h);
    q_h.finish();
    transEngine trans_JOIN_INNER_TD_5581;
    trans_JOIN_INNER_TD_5581.setq(q_h);
    trans_JOIN_INNER_TD_5581.add(&(cfg_JOIN_INNER_TD_5581_cmds));
    trans_JOIN_INNER_TD_5581.add(&(tbl_SerializeFromObject_TD_6952_input));
    q_h.finish();
    transEngine trans_JOIN_INNER_TD_6771;
    trans_JOIN_INNER_TD_6771.setq(q_h);
    trans_JOIN_INNER_TD_6771.add(&(cfg_JOIN_INNER_TD_6771_cmds));
    trans_JOIN_INNER_TD_6771.add(&(tbl_SerializeFromObject_TD_7272_input));
    q_h.finish();
    // ****************************** Events **************************** // 
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_451;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_451;
    std::vector<cl::Event> events_JOIN_INNER_TD_451;
    events_h2d_wr_JOIN_INNER_TD_451.resize(1);
    events_d2h_rd_JOIN_INNER_TD_451.resize(1);
    events_JOIN_INNER_TD_451.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_451;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_451;
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_5581;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_5581;
    std::vector<cl::Event> events_JOIN_INNER_TD_5581;
    events_h2d_wr_JOIN_INNER_TD_5581.resize(1);
    events_d2h_rd_JOIN_INNER_TD_5581.resize(1);
    events_JOIN_INNER_TD_5581.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_5581;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_5581;
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_6771;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_6771;
    std::vector<cl::Event> events_JOIN_INNER_TD_6771;
    events_h2d_wr_JOIN_INNER_TD_6771.resize(1);
    events_d2h_rd_JOIN_INNER_TD_6771.resize(1);
    events_JOIN_INNER_TD_6771.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_6771;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_6771;
    // **************************** Operations ************************** // 
    struct timeval tv_r_s, tv_r_e; 
    gettimeofday(&tv_r_s, 0); 

    struct timeval tv_r_Filter_7_566_s, tv_r_Filter_7_566_e;
    gettimeofday(&tv_r_Filter_7_566_s, 0);
    SW_Filter_TD_7659(tbl_SerializeFromObject_TD_8531_input, tbl_Filter_TD_7659_output);
    gettimeofday(&tv_r_Filter_7_566_e, 0);

    struct timeval tv_r_JOIN_INNER_6_334_s, tv_r_JOIN_INNER_6_334_e;
    gettimeofday(&tv_r_JOIN_INNER_6_334_s, 0);
    trans_JOIN_INNER_TD_6771.add(&(tbl_Filter_TD_7659_output));
    trans_JOIN_INNER_TD_6771.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_6771), &(events_h2d_wr_JOIN_INNER_TD_6771[0]));
    events_grp_JOIN_INNER_TD_6771.push_back(events_h2d_wr_JOIN_INNER_TD_6771[0]);
    krnl_JOIN_INNER_TD_6771.run(0, &(events_grp_JOIN_INNER_TD_6771), &(events_JOIN_INNER_TD_6771[0]));
    gettimeofday(&tv_r_JOIN_INNER_6_334_e, 0);

    struct timeval tv_r_JOIN_INNER_5_982_s, tv_r_JOIN_INNER_5_982_e;
    gettimeofday(&tv_r_JOIN_INNER_5_982_s, 0);
    prev_events_grp_JOIN_INNER_TD_5581.push_back(events_h2d_wr_JOIN_INNER_TD_6771[0]);
    trans_JOIN_INNER_TD_5581.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_5581), &(events_h2d_wr_JOIN_INNER_TD_5581[0]));
    events_grp_JOIN_INNER_TD_5581.push_back(events_h2d_wr_JOIN_INNER_TD_5581[0]);
    events_grp_JOIN_INNER_TD_5581.push_back(events_JOIN_INNER_TD_6771[0]);
    krnl_JOIN_INNER_TD_5581.run(0, &(events_grp_JOIN_INNER_TD_5581), &(events_JOIN_INNER_TD_5581[0]));
    gettimeofday(&tv_r_JOIN_INNER_5_982_e, 0);

    struct timeval tv_r_JOIN_INNER_4_141_s, tv_r_JOIN_INNER_4_141_e;
    gettimeofday(&tv_r_JOIN_INNER_4_141_s, 0);
    prev_events_grp_JOIN_INNER_TD_451.push_back(events_h2d_wr_JOIN_INNER_TD_5581[0]);
    trans_JOIN_INNER_TD_451.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_451), &(events_h2d_wr_JOIN_INNER_TD_451[0]));
    events_grp_JOIN_INNER_TD_451.push_back(events_h2d_wr_JOIN_INNER_TD_451[0]);
    events_grp_JOIN_INNER_TD_451.push_back(events_JOIN_INNER_TD_5581[0]);
    krnl_JOIN_INNER_TD_451.run(0, &(events_grp_JOIN_INNER_TD_451), &(events_JOIN_INNER_TD_451[0]));
    
    trans_JOIN_INNER_TD_451_out.add(&(tbl_JOIN_INNER_TD_451_output));
    trans_JOIN_INNER_TD_451_out.dev2host(0, &(events_JOIN_INNER_TD_451), &(events_d2h_rd_JOIN_INNER_TD_451[0]));
    q_h.flush();
    q_h.finish();
    gettimeofday(&tv_r_JOIN_INNER_4_141_e, 0);

    struct timeval tv_r_Filter_3_108_s, tv_r_Filter_3_108_e;
    gettimeofday(&tv_r_Filter_3_108_s, 0);
    SW_Filter_TD_3828(tbl_SerializeFromObject_TD_4773_input, tbl_Filter_TD_3828_output);
    gettimeofday(&tv_r_Filter_3_108_e, 0);

    struct timeval tv_r_JOIN_INNER_3_981_s, tv_r_JOIN_INNER_3_981_e;
    gettimeofday(&tv_r_JOIN_INNER_3_981_s, 0);
    SW_JOIN_INNER_TD_3474(tbl_JOIN_INNER_TD_451_output, tbl_SerializeFromObject_TD_4481_input, tbl_JOIN_INNER_TD_3474_output);
    gettimeofday(&tv_r_JOIN_INNER_3_981_e, 0);

    struct timeval tv_r_JOIN_INNER_2_353_s, tv_r_JOIN_INNER_2_353_e;
    gettimeofday(&tv_r_JOIN_INNER_2_353_s, 0);
    SW_JOIN_INNER_TD_2962(tbl_JOIN_INNER_TD_3474_output, tbl_Filter_TD_3828_output, tbl_JOIN_INNER_TD_2962_output);
    gettimeofday(&tv_r_JOIN_INNER_2_353_e, 0);

    struct timeval tv_r_Aggregate_1_767_s, tv_r_Aggregate_1_767_e;
    gettimeofday(&tv_r_Aggregate_1_767_s, 0);
    SW_Aggregate_TD_1875(tbl_JOIN_INNER_TD_2962_output, tbl_Aggregate_TD_1875_output);
    gettimeofday(&tv_r_Aggregate_1_767_e, 0);

    struct timeval tv_r_Sort_0_66_s, tv_r_Sort_0_66_e;
    gettimeofday(&tv_r_Sort_0_66_s, 0);
    SW_Sort_TD_0669(tbl_Aggregate_TD_1875_output, tbl_Sort_TD_0669_output);
    gettimeofday(&tv_r_Sort_0_66_e, 0);

    gettimeofday(&tv_r_e, 0); 
    // **************************** Print Execution Time ************************** // 
    std::cout << "Filter_7: " << tvdiff(&tv_r_Filter_7_566_s, &tv_r_Filter_7_566_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_8531_input: " << tbl_SerializeFromObject_TD_8531_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_6: " << tvdiff(&tv_r_JOIN_INNER_6_334_s, &tv_r_JOIN_INNER_6_334_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_7272_input: " << tbl_SerializeFromObject_TD_7272_input.getNumRow() << " " << "tbl_Filter_TD_7659_output: " << tbl_Filter_TD_7659_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_5: " << tvdiff(&tv_r_JOIN_INNER_5_982_s, &tv_r_JOIN_INNER_5_982_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_6771_output: " << tbl_JOIN_INNER_TD_6771_output.getNumRow() << " " << "tbl_SerializeFromObject_TD_6952_input: " << tbl_SerializeFromObject_TD_6952_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_4: " << tvdiff(&tv_r_JOIN_INNER_4_141_s, &tv_r_JOIN_INNER_4_141_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_5581_output: " << tbl_JOIN_INNER_TD_5581_output.getNumRow() << " " << "tbl_SerializeFromObject_TD_5598_input: " << tbl_SerializeFromObject_TD_5598_input.getNumRow() << " " << std::endl; 

    std::cout << "Filter_3: " << tvdiff(&tv_r_Filter_3_108_s, &tv_r_Filter_3_108_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_4773_input: " << tbl_SerializeFromObject_TD_4773_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_3: " << tvdiff(&tv_r_JOIN_INNER_3_981_s, &tv_r_JOIN_INNER_3_981_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_451_output: " << tbl_JOIN_INNER_TD_451_output.getNumRow() << " " << "tbl_SerializeFromObject_TD_4481_input: " << tbl_SerializeFromObject_TD_4481_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_2: " << tvdiff(&tv_r_JOIN_INNER_2_353_s, &tv_r_JOIN_INNER_2_353_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_3474_output: " << tbl_JOIN_INNER_TD_3474_output.getNumRow() << " " << "tbl_Filter_TD_3828_output: " << tbl_Filter_TD_3828_output.getNumRow() << " " << std::endl; 

    std::cout << "Aggregate_1: " << tvdiff(&tv_r_Aggregate_1_767_s, &tv_r_Aggregate_1_767_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_2962_output: " << tbl_JOIN_INNER_TD_2962_output.getNumRow() << " " << std::endl; 

    std::cout << "Sort_0: " << tvdiff(&tv_r_Sort_0_66_s, &tv_r_Sort_0_66_e) / 1000.0 << " ms " 
     << "tbl_Aggregate_TD_1875_output: " << tbl_Aggregate_TD_1875_output.getNumRow() << " " << std::endl; 

    std::cout << std::endl << " Total execution time: " << tvdiff(&tv_r_s, &tv_r_e) / 1000 << " ms"; 

    std::cout << std::endl << " Spark elapsed time: " << 46.66466 * 1000 << "ms" << std::endl; 
    return 0; 
}
