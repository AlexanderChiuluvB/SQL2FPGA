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

#include "cfgFunc_q4.hpp" 
#include "q4.hpp" 

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
    std::cout << "NOTE:running query #4\n."; 
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
    Table tbl_Sort_TD_052_output("tbl_Sort_TD_052_output", 6100000, 2, "");
    tbl_Sort_TD_052_output.allocateHost();
    Table tbl_Aggregate_TD_1168_output("tbl_Aggregate_TD_1168_output", 6100000, 2, "");
    tbl_Aggregate_TD_1168_output.allocateHost();
    Table tbl_JOIN_LEFTSEMI_TD_2456_output("tbl_JOIN_LEFTSEMI_TD_2456_output", 53000, 1, "");
    tbl_JOIN_LEFTSEMI_TD_2456_output.allocateHost();
    Table tbl_Filter_TD_3778_output("tbl_Filter_TD_3778_output", 6100000, 2, "");
    tbl_Filter_TD_3778_output.allocateHost();
    Table tbl_Filter_TD_3757_output("tbl_Filter_TD_3757_output", 6100000, 1, "");
    tbl_Filter_TD_3757_output.allocateHost();
    Table tbl_SerializeFromObject_TD_4493_input_stringRowIDSubstitute;
    tbl_SerializeFromObject_TD_4493_input_stringRowIDSubstitute = Table("orders", orders_n, 3, in_dir);
    tbl_SerializeFromObject_TD_4493_input_stringRowIDSubstitute.addCol("o_orderkey", 4);
    tbl_SerializeFromObject_TD_4493_input_stringRowIDSubstitute.addCol("o_orderpriority", 4, 1, 0);
    tbl_SerializeFromObject_TD_4493_input_stringRowIDSubstitute.addCol("o_orderdate", 4);
    tbl_SerializeFromObject_TD_4493_input_stringRowIDSubstitute.allocateHost();
    tbl_SerializeFromObject_TD_4493_input_stringRowIDSubstitute.loadHost();
    Table tbl_SerializeFromObject_TD_4493_input;
    tbl_SerializeFromObject_TD_4493_input = Table("orders", orders_n, 3, in_dir);
    tbl_SerializeFromObject_TD_4493_input.addCol("o_orderkey", 4);
    tbl_SerializeFromObject_TD_4493_input.addCol("o_orderpriority", TPCH_READ_MAXAGG_LEN+1);
    tbl_SerializeFromObject_TD_4493_input.addCol("o_orderdate", 4);
    tbl_SerializeFromObject_TD_4493_input.allocateHost();
    tbl_SerializeFromObject_TD_4493_input.loadHost();
    Table tbl_SerializeFromObject_TD_4289_input;
    tbl_SerializeFromObject_TD_4289_input = Table("lineitem", lineitem_n, 3, in_dir);
    tbl_SerializeFromObject_TD_4289_input.addCol("l_orderkey", 4);
    tbl_SerializeFromObject_TD_4289_input.addCol("l_commitdate", 4);
    tbl_SerializeFromObject_TD_4289_input.addCol("l_receiptdate", 4);
    tbl_SerializeFromObject_TD_4289_input.allocateHost();
    tbl_SerializeFromObject_TD_4289_input.loadHost();
    // ********************** Allocate Device Buffer ******************** // 
    tbl_JOIN_LEFTSEMI_TD_2456_output.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_3778_output.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_3757_output.allocateDevBuffer(context_h, 32);
    // ****************************** Config **************************** // 
    cfgCmd cfg_JOIN_LEFTSEMI_TD_2456_cmds;
    cfg_JOIN_LEFTSEMI_TD_2456_cmds.allocateHost();
    get_cfg_dat_JOIN_LEFTSEMI_TD_2456_gqe_join (cfg_JOIN_LEFTSEMI_TD_2456_cmds.cmd);
    cfg_JOIN_LEFTSEMI_TD_2456_cmds.allocateDevBuffer(context_h, 32);
    // *************************** Kernel Setup ************************* // 
    bufferTmp buftmp_h(context_h); 
    buftmp_h.initBuffer(q_h); 
    std::cout << std::endl; 
    krnlEngine krnl_JOIN_LEFTSEMI_TD_2456;
    krnl_JOIN_LEFTSEMI_TD_2456 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_LEFTSEMI_TD_2456.setup(tbl_Filter_TD_3757_output, tbl_Filter_TD_3778_output, tbl_JOIN_LEFTSEMI_TD_2456_output, cfg_JOIN_LEFTSEMI_TD_2456_cmds, buftmp_h);
    // ************************** Transfer Engine *********************** // 
    transEngine trans_JOIN_LEFTSEMI_TD_2456;
    trans_JOIN_LEFTSEMI_TD_2456.setq(q_h);
    trans_JOIN_LEFTSEMI_TD_2456.add(&(cfg_JOIN_LEFTSEMI_TD_2456_cmds));
    transEngine trans_JOIN_LEFTSEMI_TD_2456_out;
    trans_JOIN_LEFTSEMI_TD_2456_out.setq(q_h);
    q_h.finish();
    // ****************************** Events **************************** // 
    std::vector<cl::Event> events_h2d_wr_JOIN_LEFTSEMI_TD_2456;
    std::vector<cl::Event> events_d2h_rd_JOIN_LEFTSEMI_TD_2456;
    std::vector<cl::Event> events_JOIN_LEFTSEMI_TD_2456;
    events_h2d_wr_JOIN_LEFTSEMI_TD_2456.resize(1);
    events_d2h_rd_JOIN_LEFTSEMI_TD_2456.resize(1);
    events_JOIN_LEFTSEMI_TD_2456.resize(1);
    std::vector<cl::Event> events_grp_JOIN_LEFTSEMI_TD_2456;
    std::vector<cl::Event> prev_events_grp_JOIN_LEFTSEMI_TD_2456;
    // **************************** Operations ************************** // 
    struct timeval tv_r_s, tv_r_e; 
    gettimeofday(&tv_r_s, 0); 

    struct timeval tv_r_Filter_3_73_s, tv_r_Filter_3_73_e;
    gettimeofday(&tv_r_Filter_3_73_s, 0);
    SW_Filter_TD_3757(tbl_SerializeFromObject_TD_4289_input, tbl_Filter_TD_3757_output);
    gettimeofday(&tv_r_Filter_3_73_e, 0);

    struct timeval tv_r_Filter_3_570_s, tv_r_Filter_3_570_e;
    gettimeofday(&tv_r_Filter_3_570_s, 0);
    SW_Filter_TD_3778(tbl_SerializeFromObject_TD_4493_input_stringRowIDSubstitute, tbl_Filter_TD_3778_output);
    gettimeofday(&tv_r_Filter_3_570_e, 0);

    struct timeval tv_r_JOIN_LEFTSEMI_2_423_s, tv_r_JOIN_LEFTSEMI_2_423_e;
    gettimeofday(&tv_r_JOIN_LEFTSEMI_2_423_s, 0);
    trans_JOIN_LEFTSEMI_TD_2456.add(&(tbl_Filter_TD_3778_output));
    trans_JOIN_LEFTSEMI_TD_2456.add(&(tbl_Filter_TD_3757_output));
    trans_JOIN_LEFTSEMI_TD_2456.host2dev(0, &(prev_events_grp_JOIN_LEFTSEMI_TD_2456), &(events_h2d_wr_JOIN_LEFTSEMI_TD_2456[0]));
    events_grp_JOIN_LEFTSEMI_TD_2456.push_back(events_h2d_wr_JOIN_LEFTSEMI_TD_2456[0]);
    krnl_JOIN_LEFTSEMI_TD_2456.run(0, &(events_grp_JOIN_LEFTSEMI_TD_2456), &(events_JOIN_LEFTSEMI_TD_2456[0]));
    
    trans_JOIN_LEFTSEMI_TD_2456_out.add(&(tbl_JOIN_LEFTSEMI_TD_2456_output));
    trans_JOIN_LEFTSEMI_TD_2456_out.dev2host(0, &(events_JOIN_LEFTSEMI_TD_2456), &(events_d2h_rd_JOIN_LEFTSEMI_TD_2456[0]));
    q_h.flush();
    q_h.finish();
    gettimeofday(&tv_r_JOIN_LEFTSEMI_2_423_e, 0);

    struct timeval tv_r_Aggregate_1_776_s, tv_r_Aggregate_1_776_e;
    gettimeofday(&tv_r_Aggregate_1_776_s, 0);
    SW_Aggregate_TD_1168(tbl_JOIN_LEFTSEMI_TD_2456_output, tbl_SerializeFromObject_TD_4493_input, tbl_SerializeFromObject_TD_4289_input, tbl_Aggregate_TD_1168_output);
    gettimeofday(&tv_r_Aggregate_1_776_e, 0);

    struct timeval tv_r_Sort_0_147_s, tv_r_Sort_0_147_e;
    gettimeofday(&tv_r_Sort_0_147_s, 0);
    SW_Sort_TD_052(tbl_Aggregate_TD_1168_output, tbl_Sort_TD_052_output);
    gettimeofday(&tv_r_Sort_0_147_e, 0);

    gettimeofday(&tv_r_e, 0); 
    // **************************** Print Execution Time ************************** // 
    std::cout << "Filter_3: " << tvdiff(&tv_r_Filter_3_73_s, &tv_r_Filter_3_73_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_4289_input: " << tbl_SerializeFromObject_TD_4289_input.getNumRow() << " " << std::endl; 

    std::cout << "Filter_3: " << tvdiff(&tv_r_Filter_3_570_s, &tv_r_Filter_3_570_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_4493_input_stringRowIDSubstitute: " << tbl_SerializeFromObject_TD_4493_input_stringRowIDSubstitute.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_LEFTSEMI_2: " << tvdiff(&tv_r_JOIN_LEFTSEMI_2_423_s, &tv_r_JOIN_LEFTSEMI_2_423_e) / 1000.0 << " ms " 
     << "tbl_Filter_TD_3778_output: " << tbl_Filter_TD_3778_output.getNumRow() << " " << "tbl_Filter_TD_3757_output: " << tbl_Filter_TD_3757_output.getNumRow() << " " << std::endl; 

    std::cout << "Aggregate_1: " << tvdiff(&tv_r_Aggregate_1_776_s, &tv_r_Aggregate_1_776_e) / 1000.0 << " ms " 
     << "tbl_JOIN_LEFTSEMI_TD_2456_output: " << tbl_JOIN_LEFTSEMI_TD_2456_output.getNumRow() << " " << std::endl; 

    std::cout << "Sort_0: " << tvdiff(&tv_r_Sort_0_147_s, &tv_r_Sort_0_147_e) / 1000.0 << " ms " 
     << "tbl_Aggregate_TD_1168_output: " << tbl_Aggregate_TD_1168_output.getNumRow() << " " << std::endl; 

    std::cout << std::endl << " Total execution time: " << tvdiff(&tv_r_s, &tv_r_e) / 1000 << " ms"; 

    std::cout << std::endl << " Spark elapsed time: " << 40.077328 * 1000 << "ms" << std::endl; 
    return 0; 
}
