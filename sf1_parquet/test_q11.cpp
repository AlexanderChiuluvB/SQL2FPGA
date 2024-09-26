// number of overlays (w/o fusion): 5 
// number of overlays (w/ fusion): 5 
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

#include "cfgFunc_q11.hpp" 
#include "q11.hpp" 

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
    std::cout << "NOTE:running query #11\n."; 
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
    Table tbl_Sort_TD_0896_output("tbl_Sort_TD_0896_output", 6100000, 2, "");
    tbl_Sort_TD_0896_output.allocateHost();
    Table tbl_Filter_TD_1992_output("tbl_Filter_TD_1992_output", 6100000, 2, "");
    tbl_Filter_TD_1992_output.allocateHost();
    Table tbl_Aggregate_TD_2588_output_preprocess("tbl_Aggregate_TD_2588_output_preprocess", 600000, 16, "");
    tbl_Aggregate_TD_2588_output_preprocess.allocateHost();
    Table tbl_Aggregate_TD_2588_output("tbl_Aggregate_TD_2588_output", 600000, 2, "");
    tbl_Aggregate_TD_2588_output.allocateHost();
    Table tbl_Aggregate_TD_2846_output("tbl_Aggregate_TD_2846_output", 6100000, 1, "");
    tbl_Aggregate_TD_2846_output.allocateHost();
    Table tbl_JOIN_INNER_TD_3355_output("tbl_JOIN_INNER_TD_3355_output", 393, 3, "");
    tbl_JOIN_INNER_TD_3355_output.allocateHost();
    Table tbl_JOIN_INNER_TD_445_output_preprocess("tbl_JOIN_INNER_TD_445_output_preprocess", 31440, 4, "");
    tbl_JOIN_INNER_TD_445_output_preprocess.allocateHost();
    Table tbl_JOIN_INNER_TD_445_output("tbl_JOIN_INNER_TD_445_output", 31440, 4, "");
    tbl_JOIN_INNER_TD_445_output.allocateHost();
    Table tbl_Filter_TD_4735_output("tbl_Filter_TD_4735_output", 6100000, 1, "");
    tbl_Filter_TD_4735_output.allocateHost();
    Table tbl_SerializeFromObject_TD_5938_input;
    tbl_SerializeFromObject_TD_5938_input = Table("partsupp", partsupp_n, 4, in_dir);
    tbl_SerializeFromObject_TD_5938_input.addCol("ps_partkey", 4);
    tbl_SerializeFromObject_TD_5938_input.addCol("ps_suppkey", 4);
    tbl_SerializeFromObject_TD_5938_input.addCol("ps_availqty", 4);
    tbl_SerializeFromObject_TD_5938_input.addCol("ps_supplycost", 4);
    tbl_SerializeFromObject_TD_5938_input.allocateHost();
    tbl_SerializeFromObject_TD_5938_input.loadHost();
    Table tbl_SerializeFromObject_TD_5455_input;
    tbl_SerializeFromObject_TD_5455_input = Table("supplier", supplier_n, 2, in_dir);
    tbl_SerializeFromObject_TD_5455_input.addCol("s_suppkey", 4);
    tbl_SerializeFromObject_TD_5455_input.addCol("s_nationkey", 4);
    tbl_SerializeFromObject_TD_5455_input.allocateHost();
    tbl_SerializeFromObject_TD_5455_input.loadHost();
    Table tbl_SerializeFromObject_TD_5281_input;
    tbl_SerializeFromObject_TD_5281_input = Table("nation", nation_n, 2, in_dir);
    tbl_SerializeFromObject_TD_5281_input.addCol("n_nationkey", 4);
    tbl_SerializeFromObject_TD_5281_input.addCol("n_name", TPCH_READ_NATION_LEN+1);
    tbl_SerializeFromObject_TD_5281_input.allocateHost();
    tbl_SerializeFromObject_TD_5281_input.loadHost();
    // ********************** Allocate Device Buffer ******************** // 
    tbl_JOIN_INNER_TD_445_output.allocateDevBuffer(context_a, 32);
    tbl_Aggregate_TD_2588_output_preprocess.allocateDevBuffer(context_a, 33);
    tbl_JOIN_INNER_TD_3355_output.allocateDevBuffer(context_h, 32);
    tbl_JOIN_INNER_TD_445_output_preprocess.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_4735_output.allocateDevBuffer(context_a, 32);
    tbl_SerializeFromObject_TD_5938_input.allocateDevBuffer(context_h, 32);
    tbl_SerializeFromObject_TD_5455_input.allocateDevBuffer(context_h, 32);
    // ****************************** Config **************************** // 
    AggrCfgCmd cfg_Aggregate_TD_2588_cmds;
    cfg_Aggregate_TD_2588_cmds.allocateHost();
    get_cfg_dat_Aggregate_TD_2588_gqe_aggr(cfg_Aggregate_TD_2588_cmds.cmd);
    cfg_Aggregate_TD_2588_cmds.allocateDevBuffer(context_a, 32);
    AggrCfgCmd cfg_Aggregate_TD_2588_cmds_out;
    cfg_Aggregate_TD_2588_cmds_out.allocateHost();
    cfg_Aggregate_TD_2588_cmds_out.allocateDevBuffer(context_a, 33);
    cfgCmd cfg_JOIN_INNER_TD_3355_cmds;
    cfg_JOIN_INNER_TD_3355_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_3355_gqe_join (cfg_JOIN_INNER_TD_3355_cmds.cmd);
    cfg_JOIN_INNER_TD_3355_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_INNER_TD_445_cmds;
    cfg_JOIN_INNER_TD_445_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_445_gqe_join (cfg_JOIN_INNER_TD_445_cmds.cmd);
    cfg_JOIN_INNER_TD_445_cmds.allocateDevBuffer(context_h, 32);
    // *************************** Kernel Setup ************************* // 
    bufferTmp buftmp_h(context_h); 
    buftmp_h.initBuffer(q_h); 
    AggrBufferTmp buftmp_a(context_a); 
    buftmp_a.BufferInitial(q_a); 
    std::cout << std::endl; 
    AggrKrnlEngine krnl_Aggregate_TD_2588;
    krnl_Aggregate_TD_2588 = AggrKrnlEngine(program_a, q_a, "gqeAggr");
    krnl_Aggregate_TD_2588.setup(tbl_JOIN_INNER_TD_445_output, tbl_Aggregate_TD_2588_output_preprocess, cfg_Aggregate_TD_2588_cmds, cfg_Aggregate_TD_2588_cmds_out, buftmp_a);
    krnlEngine krnl_JOIN_INNER_TD_3355;
    krnl_JOIN_INNER_TD_3355 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_3355.setup(tbl_Filter_TD_4735_output, tbl_JOIN_INNER_TD_445_output, tbl_JOIN_INNER_TD_3355_output, cfg_JOIN_INNER_TD_3355_cmds, buftmp_h);
    krnlEngine krnl_JOIN_INNER_TD_445;
    krnl_JOIN_INNER_TD_445 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_445.setup(tbl_SerializeFromObject_TD_5455_input, tbl_SerializeFromObject_TD_5938_input, tbl_JOIN_INNER_TD_445_output_preprocess, cfg_JOIN_INNER_TD_445_cmds, buftmp_h);
    // ************************** Transfer Engine *********************** // 
    transEngine trans_Aggregate_TD_2588;
    trans_Aggregate_TD_2588.setq(q_a);
    trans_Aggregate_TD_2588.add(&(cfg_Aggregate_TD_2588_cmds));
    transEngine trans_Aggregate_TD_2588_out;
    trans_Aggregate_TD_2588_out.setq(q_a);
    q_a.finish();
    transEngine trans_JOIN_INNER_TD_3355;
    trans_JOIN_INNER_TD_3355.setq(q_h);
    trans_JOIN_INNER_TD_3355.add(&(cfg_JOIN_INNER_TD_3355_cmds));
    transEngine trans_JOIN_INNER_TD_3355_out;
    trans_JOIN_INNER_TD_3355_out.setq(q_h);
    q_h.finish();
    transEngine trans_JOIN_INNER_TD_445;
    trans_JOIN_INNER_TD_445.setq(q_h);
    trans_JOIN_INNER_TD_445.add(&(cfg_JOIN_INNER_TD_445_cmds));
    trans_JOIN_INNER_TD_445.add(&(tbl_SerializeFromObject_TD_5938_input));
    trans_JOIN_INNER_TD_445.add(&(tbl_SerializeFromObject_TD_5455_input));
    transEngine trans_JOIN_INNER_TD_445_out;
    trans_JOIN_INNER_TD_445_out.setq(q_h);
    q_h.finish();
    // ****************************** Events **************************** // 
    std::vector<cl::Event> events_h2d_wr_Aggregate_TD_2588;
    std::vector<cl::Event> events_d2h_rd_Aggregate_TD_2588;
    std::vector<cl::Event> events_Aggregate_TD_2588;
    events_h2d_wr_Aggregate_TD_2588.resize(1);
    events_d2h_rd_Aggregate_TD_2588.resize(1);
    events_Aggregate_TD_2588.resize(1);
    std::vector<cl::Event> events_grp_Aggregate_TD_2588;
    std::vector<cl::Event> prev_events_grp_Aggregate_TD_2588;
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_3355;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_3355;
    std::vector<cl::Event> events_JOIN_INNER_TD_3355;
    events_h2d_wr_JOIN_INNER_TD_3355.resize(1);
    events_d2h_rd_JOIN_INNER_TD_3355.resize(1);
    events_JOIN_INNER_TD_3355.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_3355;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_3355;
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_445;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_445;
    std::vector<cl::Event> events_JOIN_INNER_TD_445;
    events_h2d_wr_JOIN_INNER_TD_445.resize(1);
    events_d2h_rd_JOIN_INNER_TD_445.resize(1);
    events_JOIN_INNER_TD_445.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_445;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_445;
    // **************************** Operations ************************** // 
    struct timeval tv_r_s, tv_r_e; 
    gettimeofday(&tv_r_s, 0); 

    struct timeval tv_r_Filter_4_852_s, tv_r_Filter_4_852_e;
    gettimeofday(&tv_r_Filter_4_852_s, 0);
    SW_Filter_TD_4735(tbl_SerializeFromObject_TD_5281_input, tbl_Filter_TD_4735_output);
    gettimeofday(&tv_r_Filter_4_852_e, 0);

    struct timeval tv_r_JOIN_INNER_4_384_s, tv_r_JOIN_INNER_4_384_e;
    gettimeofday(&tv_r_JOIN_INNER_4_384_s, 0);
    trans_JOIN_INNER_TD_445.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_445), &(events_h2d_wr_JOIN_INNER_TD_445[0]));
    events_grp_JOIN_INNER_TD_445.push_back(events_h2d_wr_JOIN_INNER_TD_445[0]);
    krnl_JOIN_INNER_TD_445.run(0, &(events_grp_JOIN_INNER_TD_445), &(events_JOIN_INNER_TD_445[0]));
    
    trans_JOIN_INNER_TD_445_out.add(&(tbl_JOIN_INNER_TD_445_output_preprocess));
    trans_JOIN_INNER_TD_445_out.dev2host(0, &(events_JOIN_INNER_TD_445), &(events_d2h_rd_JOIN_INNER_TD_445[0]));
    q_h.flush();
    q_h.finish();
    WaitForEvents(events_d2h_rd_JOIN_INNER_TD_445);
    tbl_JOIN_INNER_TD_445_output_preprocess.copyTableData(&(tbl_JOIN_INNER_TD_445_output));
    gettimeofday(&tv_r_JOIN_INNER_4_384_e, 0);

    struct timeval tv_r_JOIN_INNER_3_182_s, tv_r_JOIN_INNER_3_182_e;
    gettimeofday(&tv_r_JOIN_INNER_3_182_s, 0);
    prev_events_grp_JOIN_INNER_TD_3355.push_back(events_h2d_wr_JOIN_INNER_TD_445[0]);
    trans_JOIN_INNER_TD_3355.add(&(tbl_Filter_TD_4735_output));
    trans_JOIN_INNER_TD_3355.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_3355), &(events_h2d_wr_JOIN_INNER_TD_3355[0]));
    events_grp_JOIN_INNER_TD_3355.push_back(events_h2d_wr_JOIN_INNER_TD_3355[0]);
    events_grp_JOIN_INNER_TD_3355.push_back(events_JOIN_INNER_TD_445[0]);
    krnl_JOIN_INNER_TD_3355.run(0, &(events_grp_JOIN_INNER_TD_3355), &(events_JOIN_INNER_TD_3355[0]));
    
    trans_JOIN_INNER_TD_3355_out.add(&(tbl_JOIN_INNER_TD_3355_output));
    trans_JOIN_INNER_TD_3355_out.dev2host(0, &(events_JOIN_INNER_TD_3355), &(events_d2h_rd_JOIN_INNER_TD_3355[0]));
    q_h.flush();
    q_h.finish();
    gettimeofday(&tv_r_JOIN_INNER_3_182_e, 0);

    struct timeval tv_r_Aggregate_2_415_s, tv_r_Aggregate_2_415_e;
    gettimeofday(&tv_r_Aggregate_2_415_s, 0);
    SW_Aggregate_TD_2846(tbl_JOIN_INNER_TD_3355_output, tbl_Aggregate_TD_2846_output);
    gettimeofday(&tv_r_Aggregate_2_415_e, 0);

    struct timeval tv_r_Aggregate_2_438_s, tv_r_Aggregate_2_438_e;
    gettimeofday(&tv_r_Aggregate_2_438_s, 0);
    trans_Aggregate_TD_2588.add(&(tbl_JOIN_INNER_TD_445_output));
    trans_Aggregate_TD_2588.add(&(tbl_Filter_TD_4735_output));
    trans_Aggregate_TD_2588.host2dev(0, &(prev_events_grp_Aggregate_TD_2588), &(events_h2d_wr_Aggregate_TD_2588[0]));
    events_grp_Aggregate_TD_2588.push_back(events_h2d_wr_Aggregate_TD_2588[0]);
    krnl_Aggregate_TD_2588.run(0, &(events_grp_Aggregate_TD_2588), &(events_Aggregate_TD_2588[0]));
    
    trans_Aggregate_TD_2588_out.add(&(tbl_Aggregate_TD_2588_output_preprocess));
    trans_Aggregate_TD_2588_out.dev2host(0, &(events_Aggregate_TD_2588), &(events_d2h_rd_Aggregate_TD_2588[0]));
    q_a.flush();
    q_a.finish();
    
    SW_Aggregate_TD_2588_consolidate(tbl_Aggregate_TD_2588_output_preprocess, tbl_Aggregate_TD_2588_output);
    gettimeofday(&tv_r_Aggregate_2_438_e, 0);

    struct timeval tv_r_Filter_1_192_s, tv_r_Filter_1_192_e;
    gettimeofday(&tv_r_Filter_1_192_s, 0);
    SW_Filter_TD_1992(tbl_Aggregate_TD_2588_output, tbl_Aggregate_TD_2846_output, tbl_Filter_TD_1992_output);
    gettimeofday(&tv_r_Filter_1_192_e, 0);

    struct timeval tv_r_Sort_0_922_s, tv_r_Sort_0_922_e;
    gettimeofday(&tv_r_Sort_0_922_s, 0);
    SW_Sort_TD_0896(tbl_Filter_TD_1992_output, tbl_Sort_TD_0896_output);
    gettimeofday(&tv_r_Sort_0_922_e, 0);

    gettimeofday(&tv_r_e, 0); 
    // **************************** Print Execution Time ************************** // 
    std::cout << "Filter_4: " << tvdiff(&tv_r_Filter_4_852_s, &tv_r_Filter_4_852_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_5281_input: " << tbl_SerializeFromObject_TD_5281_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_4: " << tvdiff(&tv_r_JOIN_INNER_4_384_s, &tv_r_JOIN_INNER_4_384_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_5938_input: " << tbl_SerializeFromObject_TD_5938_input.getNumRow() << " " << "tbl_SerializeFromObject_TD_5455_input: " << tbl_SerializeFromObject_TD_5455_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_3: " << tvdiff(&tv_r_JOIN_INNER_3_182_s, &tv_r_JOIN_INNER_3_182_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_445_output: " << tbl_JOIN_INNER_TD_445_output.getNumRow() << " " << "tbl_Filter_TD_4735_output: " << tbl_Filter_TD_4735_output.getNumRow() << " " << std::endl; 

    std::cout << "Aggregate_2: " << tvdiff(&tv_r_Aggregate_2_415_s, &tv_r_Aggregate_2_415_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_3355_output: " << tbl_JOIN_INNER_TD_3355_output.getNumRow() << " " << std::endl; 

    std::cout << "Aggregate_2: " << tvdiff(&tv_r_Aggregate_2_438_s, &tv_r_Aggregate_2_438_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_445_output: " << tbl_JOIN_INNER_TD_445_output.getNumRow() << " " << "tbl_Filter_TD_4735_output: " << tbl_Filter_TD_4735_output.getNumRow() << " " << std::endl; 

    std::cout << "Filter_1: " << tvdiff(&tv_r_Filter_1_192_s, &tv_r_Filter_1_192_e) / 1000.0 << " ms " 
     << "tbl_Aggregate_TD_2588_output: " << tbl_Aggregate_TD_2588_output.getNumRow() << " " << "tbl_Aggregate_TD_2846_output: " << tbl_Aggregate_TD_2846_output.getNumRow() << " " << std::endl; 

    std::cout << "Sort_0: " << tvdiff(&tv_r_Sort_0_922_s, &tv_r_Sort_0_922_e) / 1000.0 << " ms " 
     << "tbl_Filter_TD_1992_output: " << tbl_Filter_TD_1992_output.getNumRow() << " " << std::endl; 

    std::cout << std::endl << " Total execution time: " << tvdiff(&tv_r_s, &tv_r_e) / 1000 << " ms"; 

    std::cout << std::endl << " Spark elapsed time: " << 1.7835687 * 1000 << "ms" << std::endl; 
    return 0; 
}
