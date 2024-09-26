// number of overlays (w/o fusion): 1 
// number of overlays (w/ fusion): 1 
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

#include "cfgFunc_q17.hpp" 
#include "q17.hpp" 

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
    std::cout << "NOTE:running query #17\n."; 
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
    Table tbl_Aggregate_TD_02_output("tbl_Aggregate_TD_02_output", 6100000, 1, "");
    tbl_Aggregate_TD_02_output.allocateHost();
    Table tbl_JOIN_INNER_TD_165_output("tbl_JOIN_INNER_TD_165_output", 6100000, 1, "");
    tbl_JOIN_INNER_TD_165_output.allocateHost();
    Table tbl_JOIN_INNER_TD_248_output("tbl_JOIN_INNER_TD_248_output", 1507, 3, "");
    tbl_JOIN_INNER_TD_248_output.allocateHost();
    Table tbl_Aggregate_TD_3595_output("tbl_Aggregate_TD_3595_output", 6100000, 2, "");
    tbl_Aggregate_TD_3595_output.allocateHost();
    Table tbl_SerializeFromObject_TD_3949_input;
    tbl_SerializeFromObject_TD_3949_input = Table("lineitem", lineitem_n, 3, in_dir);
    tbl_SerializeFromObject_TD_3949_input.addCol("l_partkey", 4);
    tbl_SerializeFromObject_TD_3949_input.addCol("l_quantity", 4);
    tbl_SerializeFromObject_TD_3949_input.addCol("l_extendedprice", 4);
    tbl_SerializeFromObject_TD_3949_input.allocateHost();
    tbl_SerializeFromObject_TD_3949_input.loadHost();
    Table tbl_Filter_TD_3458_output("tbl_Filter_TD_3458_output", 6100000, 1, "");
    tbl_Filter_TD_3458_output.allocateHost();
    Table tbl_SerializeFromObject_TD_4718_input;
    tbl_SerializeFromObject_TD_4718_input = Table("lineitem", lineitem_n, 2, in_dir);
    tbl_SerializeFromObject_TD_4718_input.addCol("l_partkey", 4);
    tbl_SerializeFromObject_TD_4718_input.addCol("l_quantity", 4);
    tbl_SerializeFromObject_TD_4718_input.allocateHost();
    tbl_SerializeFromObject_TD_4718_input.loadHost();
    Table tbl_SerializeFromObject_TD_4449_input;
    tbl_SerializeFromObject_TD_4449_input = Table("part", part_n, 3, in_dir);
    tbl_SerializeFromObject_TD_4449_input.addCol("p_partkey", 4);
    tbl_SerializeFromObject_TD_4449_input.addCol("p_brand", TPCH_READ_P_BRND_LEN+1);
    tbl_SerializeFromObject_TD_4449_input.addCol("p_container", TPCH_READ_P_CNTR_LEN+1);
    tbl_SerializeFromObject_TD_4449_input.allocateHost();
    tbl_SerializeFromObject_TD_4449_input.loadHost();
    // ********************** Allocate Device Buffer ******************** // 
    tbl_JOIN_INNER_TD_248_output.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_3949_input.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_3458_output.allocateDevBuffer(context_h, 32);
    // ****************************** Config **************************** // 
    cfgCmd cfg_JOIN_INNER_TD_248_cmds;
    cfg_JOIN_INNER_TD_248_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_248_gqe_join (cfg_JOIN_INNER_TD_248_cmds.cmd);
    cfg_JOIN_INNER_TD_248_cmds.allocateDevBuffer(context_h, 32);
    // *************************** Kernel Setup ************************* // 
    bufferTmp buftmp_h(context_h); 
    buftmp_h.initBuffer(q_h); 
    std::cout << std::endl; 
    krnlEngine krnl_JOIN_INNER_TD_248;
    krnl_JOIN_INNER_TD_248 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_248.setup(tbl_Filter_TD_3458_output, tbl_SerializeFromObject_TD_3949_input, tbl_JOIN_INNER_TD_248_output, cfg_JOIN_INNER_TD_248_cmds, buftmp_h);
    // ************************** Transfer Engine *********************** // 
    transEngine trans_JOIN_INNER_TD_248;
    trans_JOIN_INNER_TD_248.setq(q_h);
    trans_JOIN_INNER_TD_248.add(&(cfg_JOIN_INNER_TD_248_cmds));
    trans_JOIN_INNER_TD_248.add(&(tbl_SerializeFromObject_TD_3949_input));
    transEngine trans_JOIN_INNER_TD_248_out;
    trans_JOIN_INNER_TD_248_out.setq(q_h);
    q_h.finish();
    // ****************************** Events **************************** // 
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_248;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_248;
    std::vector<cl::Event> events_JOIN_INNER_TD_248;
    events_h2d_wr_JOIN_INNER_TD_248.resize(1);
    events_d2h_rd_JOIN_INNER_TD_248.resize(1);
    events_JOIN_INNER_TD_248.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_248;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_248;
    // **************************** Operations ************************** // 
    struct timeval tv_r_s, tv_r_e; 
    gettimeofday(&tv_r_s, 0); 

    struct timeval tv_r_Filter_3_223_s, tv_r_Filter_3_223_e;
    gettimeofday(&tv_r_Filter_3_223_s, 0);
    SW_Filter_TD_3458(tbl_SerializeFromObject_TD_4449_input, tbl_Filter_TD_3458_output);
    gettimeofday(&tv_r_Filter_3_223_e, 0);

    struct timeval tv_r_Aggregate_3_87_s, tv_r_Aggregate_3_87_e;
    gettimeofday(&tv_r_Aggregate_3_87_s, 0);
    SW_Aggregate_TD_3595(tbl_SerializeFromObject_TD_4718_input, tbl_Aggregate_TD_3595_output);
    gettimeofday(&tv_r_Aggregate_3_87_e, 0);

    struct timeval tv_r_JOIN_INNER_2_275_s, tv_r_JOIN_INNER_2_275_e;
    gettimeofday(&tv_r_JOIN_INNER_2_275_s, 0);
    trans_JOIN_INNER_TD_248.add(&(tbl_Filter_TD_3458_output));
    trans_JOIN_INNER_TD_248.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_248), &(events_h2d_wr_JOIN_INNER_TD_248[0]));
    events_grp_JOIN_INNER_TD_248.push_back(events_h2d_wr_JOIN_INNER_TD_248[0]);
    krnl_JOIN_INNER_TD_248.run(0, &(events_grp_JOIN_INNER_TD_248), &(events_JOIN_INNER_TD_248[0]));
    
    trans_JOIN_INNER_TD_248_out.add(&(tbl_JOIN_INNER_TD_248_output));
    trans_JOIN_INNER_TD_248_out.dev2host(0, &(events_JOIN_INNER_TD_248), &(events_d2h_rd_JOIN_INNER_TD_248[0]));
    q_h.flush();
    q_h.finish();
    gettimeofday(&tv_r_JOIN_INNER_2_275_e, 0);

    struct timeval tv_r_JOIN_INNER_1_406_s, tv_r_JOIN_INNER_1_406_e;
    gettimeofday(&tv_r_JOIN_INNER_1_406_s, 0);
    SW_JOIN_INNER_TD_165(tbl_JOIN_INNER_TD_248_output, tbl_Aggregate_TD_3595_output, tbl_JOIN_INNER_TD_165_output);
    gettimeofday(&tv_r_JOIN_INNER_1_406_e, 0);

    struct timeval tv_r_Aggregate_0_530_s, tv_r_Aggregate_0_530_e;
    gettimeofday(&tv_r_Aggregate_0_530_s, 0);
    SW_Aggregate_TD_02(tbl_JOIN_INNER_TD_165_output, tbl_Aggregate_TD_02_output);
    gettimeofday(&tv_r_Aggregate_0_530_e, 0);

    gettimeofday(&tv_r_e, 0); 
    // **************************** Print Execution Time ************************** // 
    std::cout << "Filter_3: " << tvdiff(&tv_r_Filter_3_223_s, &tv_r_Filter_3_223_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_4449_input: " << tbl_SerializeFromObject_TD_4449_input.getNumRow() << " " << std::endl; 

    std::cout << "Aggregate_3: " << tvdiff(&tv_r_Aggregate_3_87_s, &tv_r_Aggregate_3_87_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_4718_input: " << tbl_SerializeFromObject_TD_4718_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_2: " << tvdiff(&tv_r_JOIN_INNER_2_275_s, &tv_r_JOIN_INNER_2_275_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_3949_input: " << tbl_SerializeFromObject_TD_3949_input.getNumRow() << " " << "tbl_Filter_TD_3458_output: " << tbl_Filter_TD_3458_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_1: " << tvdiff(&tv_r_JOIN_INNER_1_406_s, &tv_r_JOIN_INNER_1_406_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_248_output: " << tbl_JOIN_INNER_TD_248_output.getNumRow() << " " << "tbl_Aggregate_TD_3595_output: " << tbl_Aggregate_TD_3595_output.getNumRow() << " " << std::endl; 

    std::cout << "Aggregate_0: " << tvdiff(&tv_r_Aggregate_0_530_s, &tv_r_Aggregate_0_530_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_165_output: " << tbl_JOIN_INNER_TD_165_output.getNumRow() << " " << std::endl; 

    std::cout << std::endl << " Total execution time: " << tvdiff(&tv_r_s, &tv_r_e) / 1000 << " ms"; 

    std::cout << std::endl << " Spark elapsed time: " << 56.020668 * 1000 << "ms" << std::endl; 
    return 0; 
}
