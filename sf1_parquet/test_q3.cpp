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

#include "cfgFunc_q3.hpp" 
#include "q3.hpp" 

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
    std::cout << "NOTE:running query #3\n."; 
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
    Table tbl_Sort_TD_041_output("tbl_Sort_TD_041_output", 6100000, 4, "");
    tbl_Sort_TD_041_output.allocateHost();
    Table tbl_Aggregate_TD_1746_output_preprocess("tbl_Aggregate_TD_1746_output_preprocess", 24000, 16, "");
    tbl_Aggregate_TD_1746_output_preprocess.allocateHost();
    Table tbl_Aggregate_TD_1746_output("tbl_Aggregate_TD_1746_output", 24000, 4, "");
    tbl_Aggregate_TD_1746_output.allocateHost();
    Table tbl_JOIN_INNER_TD_2152_output_preprocess("tbl_JOIN_INNER_TD_2152_output_preprocess", 30000, 5, "");
    tbl_JOIN_INNER_TD_2152_output_preprocess.allocateHost();
    Table tbl_JOIN_INNER_TD_2152_output("tbl_JOIN_INNER_TD_2152_output", 30000, 5, "");
    tbl_JOIN_INNER_TD_2152_output.allocateHost();
    Table tbl_JOIN_INNER_TD_3968_output("tbl_JOIN_INNER_TD_3968_output", 150000, 3, "");
    tbl_JOIN_INNER_TD_3968_output.allocateHost();
    Table tbl_Filter_TD_3948_output("tbl_Filter_TD_3948_output", 6100000, 3, "");
    tbl_Filter_TD_3948_output.allocateHost();
    Table tbl_Filter_TD_4390_output("tbl_Filter_TD_4390_output", 6100000, 1, "");
    tbl_Filter_TD_4390_output.allocateHost();
    Table tbl_Filter_TD_4451_output("tbl_Filter_TD_4451_output", 6100000, 4, "");
    tbl_Filter_TD_4451_output.allocateHost();
    Table tbl_SerializeFromObject_TD_4314_input;
    tbl_SerializeFromObject_TD_4314_input = Table("lineitem", lineitem_n, 4, in_dir);
    tbl_SerializeFromObject_TD_4314_input.addCol("l_orderkey", 4);
    tbl_SerializeFromObject_TD_4314_input.addCol("l_extendedprice", 4);
    tbl_SerializeFromObject_TD_4314_input.addCol("l_discount", 4);
    tbl_SerializeFromObject_TD_4314_input.addCol("l_shipdate", 4);
    tbl_SerializeFromObject_TD_4314_input.allocateHost();
    tbl_SerializeFromObject_TD_4314_input.loadHost();
    Table tbl_SerializeFromObject_TD_5351_input;
    tbl_SerializeFromObject_TD_5351_input = Table("customer", customer_n, 2, in_dir);
    tbl_SerializeFromObject_TD_5351_input.addCol("c_custkey", 4);
    tbl_SerializeFromObject_TD_5351_input.addCol("c_mktsegment", TPCH_READ_MAXAGG_LEN+1);
    tbl_SerializeFromObject_TD_5351_input.allocateHost();
    tbl_SerializeFromObject_TD_5351_input.loadHost();
    Table tbl_SerializeFromObject_TD_5145_input;
    tbl_SerializeFromObject_TD_5145_input = Table("orders", orders_n, 4, in_dir);
    tbl_SerializeFromObject_TD_5145_input.addCol("o_orderkey", 4);
    tbl_SerializeFromObject_TD_5145_input.addCol("o_custkey", 4);
    tbl_SerializeFromObject_TD_5145_input.addCol("o_orderdate", 4);
    tbl_SerializeFromObject_TD_5145_input.addCol("o_shippriority", 4);
    tbl_SerializeFromObject_TD_5145_input.allocateHost();
    tbl_SerializeFromObject_TD_5145_input.loadHost();
    // ********************** Allocate Device Buffer ******************** // 
    tbl_JOIN_INNER_TD_2152_output.allocateDevBuffer(context_a, 32);
    tbl_Aggregate_TD_1746_output_preprocess.allocateDevBuffer(context_a, 33);
    tbl_JOIN_INNER_TD_2152_output_preprocess.allocateDevBuffer(context_h, 32);
    tbl_JOIN_INNER_TD_3968_output.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_3948_output.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_4390_output.allocateDevBuffer(context_h, 32);
    tbl_Filter_TD_4451_output.allocateDevBuffer(context_h, 32);
    // ****************************** Config **************************** // 
    AggrCfgCmd cfg_Aggregate_TD_1746_cmds;
    cfg_Aggregate_TD_1746_cmds.allocateHost();
    get_cfg_dat_Aggregate_TD_1746_gqe_aggr(cfg_Aggregate_TD_1746_cmds.cmd);
    cfg_Aggregate_TD_1746_cmds.allocateDevBuffer(context_a, 32);
    AggrCfgCmd cfg_Aggregate_TD_1746_cmds_out;
    cfg_Aggregate_TD_1746_cmds_out.allocateHost();
    cfg_Aggregate_TD_1746_cmds_out.allocateDevBuffer(context_a, 33);
    cfgCmd cfg_JOIN_INNER_TD_2152_cmds;
    cfg_JOIN_INNER_TD_2152_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_2152_gqe_join (cfg_JOIN_INNER_TD_2152_cmds.cmd);
    cfg_JOIN_INNER_TD_2152_cmds.allocateDevBuffer(context_h, 32);
    cfgCmd cfg_JOIN_INNER_TD_3968_cmds;
    cfg_JOIN_INNER_TD_3968_cmds.allocateHost();
    get_cfg_dat_JOIN_INNER_TD_3968_gqe_join (cfg_JOIN_INNER_TD_3968_cmds.cmd);
    cfg_JOIN_INNER_TD_3968_cmds.allocateDevBuffer(context_h, 32);
    // *************************** Kernel Setup ************************* // 
    bufferTmp buftmp_h(context_h); 
    buftmp_h.initBuffer(q_h); 
    AggrBufferTmp buftmp_a(context_a); 
    buftmp_a.BufferInitial(q_a); 
    std::cout << std::endl; 
    AggrKrnlEngine krnl_Aggregate_TD_1746;
    krnl_Aggregate_TD_1746 = AggrKrnlEngine(program_a, q_a, "gqeAggr");
    krnl_Aggregate_TD_1746.setup(tbl_JOIN_INNER_TD_2152_output, tbl_Aggregate_TD_1746_output_preprocess, cfg_Aggregate_TD_1746_cmds, cfg_Aggregate_TD_1746_cmds_out, buftmp_a);
    krnlEngine krnl_JOIN_INNER_TD_2152;
    krnl_JOIN_INNER_TD_2152 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_2152.setup(tbl_Filter_TD_3948_output, tbl_JOIN_INNER_TD_3968_output, tbl_JOIN_INNER_TD_2152_output_preprocess, cfg_JOIN_INNER_TD_2152_cmds, buftmp_h);
    krnlEngine krnl_JOIN_INNER_TD_3968;
    krnl_JOIN_INNER_TD_3968 = krnlEngine(program_h, q_h, "gqeJoin");
    krnl_JOIN_INNER_TD_3968.setup(tbl_Filter_TD_4390_output, tbl_Filter_TD_4451_output, tbl_JOIN_INNER_TD_3968_output, cfg_JOIN_INNER_TD_3968_cmds, buftmp_h);
    // ************************** Transfer Engine *********************** // 
    transEngine trans_Aggregate_TD_1746;
    trans_Aggregate_TD_1746.setq(q_a);
    trans_Aggregate_TD_1746.add(&(cfg_Aggregate_TD_1746_cmds));
    transEngine trans_Aggregate_TD_1746_out;
    trans_Aggregate_TD_1746_out.setq(q_a);
    q_a.finish();
    transEngine trans_JOIN_INNER_TD_2152;
    trans_JOIN_INNER_TD_2152.setq(q_h);
    trans_JOIN_INNER_TD_2152.add(&(cfg_JOIN_INNER_TD_2152_cmds));
    transEngine trans_JOIN_INNER_TD_2152_out;
    trans_JOIN_INNER_TD_2152_out.setq(q_h);
    q_h.finish();
    transEngine trans_JOIN_INNER_TD_3968;
    trans_JOIN_INNER_TD_3968.setq(q_h);
    trans_JOIN_INNER_TD_3968.add(&(cfg_JOIN_INNER_TD_3968_cmds));
    q_h.finish();
    // ****************************** Events **************************** // 
    std::vector<cl::Event> events_h2d_wr_Aggregate_TD_1746;
    std::vector<cl::Event> events_d2h_rd_Aggregate_TD_1746;
    std::vector<cl::Event> events_Aggregate_TD_1746;
    events_h2d_wr_Aggregate_TD_1746.resize(1);
    events_d2h_rd_Aggregate_TD_1746.resize(1);
    events_Aggregate_TD_1746.resize(1);
    std::vector<cl::Event> events_grp_Aggregate_TD_1746;
    std::vector<cl::Event> prev_events_grp_Aggregate_TD_1746;
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_2152;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_2152;
    std::vector<cl::Event> events_JOIN_INNER_TD_2152;
    events_h2d_wr_JOIN_INNER_TD_2152.resize(1);
    events_d2h_rd_JOIN_INNER_TD_2152.resize(1);
    events_JOIN_INNER_TD_2152.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_2152;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_2152;
    std::vector<cl::Event> events_h2d_wr_JOIN_INNER_TD_3968;
    std::vector<cl::Event> events_d2h_rd_JOIN_INNER_TD_3968;
    std::vector<cl::Event> events_JOIN_INNER_TD_3968;
    events_h2d_wr_JOIN_INNER_TD_3968.resize(1);
    events_d2h_rd_JOIN_INNER_TD_3968.resize(1);
    events_JOIN_INNER_TD_3968.resize(1);
    std::vector<cl::Event> events_grp_JOIN_INNER_TD_3968;
    std::vector<cl::Event> prev_events_grp_JOIN_INNER_TD_3968;
    // **************************** Operations ************************** // 
    struct timeval tv_r_s, tv_r_e; 
    gettimeofday(&tv_r_s, 0); 

    struct timeval tv_r_Filter_4_60_s, tv_r_Filter_4_60_e;
    gettimeofday(&tv_r_Filter_4_60_s, 0);
    SW_Filter_TD_4451(tbl_SerializeFromObject_TD_5145_input, tbl_Filter_TD_4451_output);
    gettimeofday(&tv_r_Filter_4_60_e, 0);

    struct timeval tv_r_Filter_4_289_s, tv_r_Filter_4_289_e;
    gettimeofday(&tv_r_Filter_4_289_s, 0);
    SW_Filter_TD_4390(tbl_SerializeFromObject_TD_5351_input, tbl_Filter_TD_4390_output);
    gettimeofday(&tv_r_Filter_4_289_e, 0);

    struct timeval tv_r_Filter_3_449_s, tv_r_Filter_3_449_e;
    gettimeofday(&tv_r_Filter_3_449_s, 0);
    SW_Filter_TD_3948(tbl_SerializeFromObject_TD_4314_input, tbl_Filter_TD_3948_output);
    gettimeofday(&tv_r_Filter_3_449_e, 0);

    struct timeval tv_r_JOIN_INNER_3_302_s, tv_r_JOIN_INNER_3_302_e;
    gettimeofday(&tv_r_JOIN_INNER_3_302_s, 0);
    trans_JOIN_INNER_TD_3968.add(&(tbl_Filter_TD_4390_output));
    trans_JOIN_INNER_TD_3968.add(&(tbl_Filter_TD_4451_output));
    trans_JOIN_INNER_TD_3968.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_3968), &(events_h2d_wr_JOIN_INNER_TD_3968[0]));
    events_grp_JOIN_INNER_TD_3968.push_back(events_h2d_wr_JOIN_INNER_TD_3968[0]);
    krnl_JOIN_INNER_TD_3968.run(0, &(events_grp_JOIN_INNER_TD_3968), &(events_JOIN_INNER_TD_3968[0]));
    gettimeofday(&tv_r_JOIN_INNER_3_302_e, 0);

    struct timeval tv_r_JOIN_INNER_2_624_s, tv_r_JOIN_INNER_2_624_e;
    gettimeofday(&tv_r_JOIN_INNER_2_624_s, 0);
    prev_events_grp_JOIN_INNER_TD_2152.push_back(events_h2d_wr_JOIN_INNER_TD_3968[0]);
    trans_JOIN_INNER_TD_2152.add(&(tbl_Filter_TD_3948_output));
    trans_JOIN_INNER_TD_2152.host2dev(0, &(prev_events_grp_JOIN_INNER_TD_2152), &(events_h2d_wr_JOIN_INNER_TD_2152[0]));
    events_grp_JOIN_INNER_TD_2152.push_back(events_h2d_wr_JOIN_INNER_TD_2152[0]);
    events_grp_JOIN_INNER_TD_2152.push_back(events_JOIN_INNER_TD_3968[0]);
    krnl_JOIN_INNER_TD_2152.run(0, &(events_grp_JOIN_INNER_TD_2152), &(events_JOIN_INNER_TD_2152[0]));
    
    trans_JOIN_INNER_TD_2152_out.add(&(tbl_JOIN_INNER_TD_2152_output_preprocess));
    trans_JOIN_INNER_TD_2152_out.dev2host(0, &(events_JOIN_INNER_TD_2152), &(events_d2h_rd_JOIN_INNER_TD_2152[0]));
    q_h.flush();
    q_h.finish();
    WaitForEvents(events_d2h_rd_JOIN_INNER_TD_2152);
    tbl_JOIN_INNER_TD_2152_output_preprocess.copyTableData(&(tbl_JOIN_INNER_TD_2152_output));
    gettimeofday(&tv_r_JOIN_INNER_2_624_e, 0);

    struct timeval tv_r_Aggregate_1_376_s, tv_r_Aggregate_1_376_e;
    gettimeofday(&tv_r_Aggregate_1_376_s, 0);
    trans_Aggregate_TD_1746.add(&(tbl_JOIN_INNER_TD_2152_output));
    trans_Aggregate_TD_1746.host2dev(0, &(prev_events_grp_Aggregate_TD_1746), &(events_h2d_wr_Aggregate_TD_1746[0]));
    events_grp_Aggregate_TD_1746.push_back(events_h2d_wr_Aggregate_TD_1746[0]);
    krnl_Aggregate_TD_1746.run(0, &(events_grp_Aggregate_TD_1746), &(events_Aggregate_TD_1746[0]));
    
    trans_Aggregate_TD_1746_out.add(&(tbl_Aggregate_TD_1746_output_preprocess));
    trans_Aggregate_TD_1746_out.dev2host(0, &(events_Aggregate_TD_1746), &(events_d2h_rd_Aggregate_TD_1746[0]));
    q_a.flush();
    q_a.finish();
    
    SW_Aggregate_TD_1746_consolidate(tbl_Aggregate_TD_1746_output_preprocess, tbl_Aggregate_TD_1746_output);
    gettimeofday(&tv_r_Aggregate_1_376_e, 0);

    struct timeval tv_r_Sort_0_210_s, tv_r_Sort_0_210_e;
    gettimeofday(&tv_r_Sort_0_210_s, 0);
    SW_Sort_TD_041(tbl_Aggregate_TD_1746_output, tbl_Sort_TD_041_output);
    gettimeofday(&tv_r_Sort_0_210_e, 0);

    gettimeofday(&tv_r_e, 0); 
    // **************************** Print Execution Time ************************** // 
    std::cout << "Filter_4: " << tvdiff(&tv_r_Filter_4_60_s, &tv_r_Filter_4_60_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_5145_input: " << tbl_SerializeFromObject_TD_5145_input.getNumRow() << " " << std::endl; 

    std::cout << "Filter_4: " << tvdiff(&tv_r_Filter_4_289_s, &tv_r_Filter_4_289_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_5351_input: " << tbl_SerializeFromObject_TD_5351_input.getNumRow() << " " << std::endl; 

    std::cout << "Filter_3: " << tvdiff(&tv_r_Filter_3_449_s, &tv_r_Filter_3_449_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_4314_input: " << tbl_SerializeFromObject_TD_4314_input.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_3: " << tvdiff(&tv_r_JOIN_INNER_3_302_s, &tv_r_JOIN_INNER_3_302_e) / 1000.0 << " ms " 
     << "tbl_Filter_TD_4390_output: " << tbl_Filter_TD_4390_output.getNumRow() << " " << "tbl_Filter_TD_4451_output: " << tbl_Filter_TD_4451_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_2: " << tvdiff(&tv_r_JOIN_INNER_2_624_s, &tv_r_JOIN_INNER_2_624_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_3968_output: " << tbl_JOIN_INNER_TD_3968_output.getNumRow() << " " << "tbl_Filter_TD_3948_output: " << tbl_Filter_TD_3948_output.getNumRow() << " " << std::endl; 

    std::cout << "Aggregate_1: " << tvdiff(&tv_r_Aggregate_1_376_s, &tv_r_Aggregate_1_376_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_2152_output: " << tbl_JOIN_INNER_TD_2152_output.getNumRow() << " " << std::endl; 

    std::cout << "Sort_0: " << tvdiff(&tv_r_Sort_0_210_s, &tv_r_Sort_0_210_e) / 1000.0 << " ms " 
     << "tbl_Aggregate_TD_1746_output: " << tbl_Aggregate_TD_1746_output.getNumRow() << " " << std::endl; 

    std::cout << std::endl << " Total execution time: " << tvdiff(&tv_r_s, &tv_r_e) / 1000 << " ms"; 

    std::cout << std::endl << " Spark elapsed time: " << 40.869675 * 1000 << "ms" << std::endl; 
    return 0; 
}
