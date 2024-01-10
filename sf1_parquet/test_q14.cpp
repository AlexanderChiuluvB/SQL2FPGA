// number of overlays (w/o fusion): 0 
// number of overlays (w/ fusion): 0 
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

#include "cfgFunc_q14.hpp" 
#include "q14.hpp" 

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
    std::cout << "NOTE:running query #14\n."; 
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
    // ****************************** Tables **************************** // 
    Table tbl_Aggregate_TD_0567_output("tbl_Aggregate_TD_0567_output", 6100000, 1, "");
    tbl_Aggregate_TD_0567_output.allocateHost();
    Table tbl_JOIN_INNER_TD_141_output("tbl_JOIN_INNER_TD_141_output", 6100000, 3, "");
    tbl_JOIN_INNER_TD_141_output.allocateHost();
    Table tbl_Project_TD_2565_output("tbl_Project_TD_2565_output", 6100000, 3, "");
    tbl_Project_TD_2565_output.allocateHost();
    Table tbl_Project_TD_2822_output("tbl_Project_TD_2822_output", 6100000, 2, "");
    tbl_Project_TD_2822_output.allocateHost();
    Table tbl_Filter_TD_3685_output("tbl_Filter_TD_3685_output", 6100000, 3, "");
    tbl_Filter_TD_3685_output.allocateHost();
    Table tbl_SerializeFromObject_TD_4305_input;
    tbl_SerializeFromObject_TD_4305_input = Table("part", part_n, 2, in_dir);
    tbl_SerializeFromObject_TD_4305_input.addCol("p_partkey", 4);
    tbl_SerializeFromObject_TD_4305_input.addCol("p_type", TPCH_READ_P_TYPE_LEN+1);
    tbl_SerializeFromObject_TD_4305_input.allocateHost();
    tbl_SerializeFromObject_TD_4305_input.loadHost();
    Table tbl_SerializeFromObject_TD_4369_input;
    tbl_SerializeFromObject_TD_4369_input = Table("lineitem", lineitem_n, 4, in_dir);
    tbl_SerializeFromObject_TD_4369_input.addCol("l_partkey", 4);
    tbl_SerializeFromObject_TD_4369_input.addCol("l_extendedprice", 4);
    tbl_SerializeFromObject_TD_4369_input.addCol("l_discount", 4);
    tbl_SerializeFromObject_TD_4369_input.addCol("l_shipdate", 4);
    tbl_SerializeFromObject_TD_4369_input.allocateHost();
    tbl_SerializeFromObject_TD_4369_input.loadHost();
    // ********************** Allocate Device Buffer ******************** // 
    // ****************************** Config **************************** // 
    // *************************** Kernel Setup ************************* // 
    std::cout << std::endl; 
    // ************************** Transfer Engine *********************** // 
    // ****************************** Events **************************** // 
    // **************************** Operations ************************** // 
    struct timeval tv_r_s, tv_r_e; 
    gettimeofday(&tv_r_s, 0); 

    struct timeval tv_r_Filter_3_99_s, tv_r_Filter_3_99_e;
    gettimeofday(&tv_r_Filter_3_99_s, 0);
    SW_Filter_TD_3685(tbl_SerializeFromObject_TD_4369_input, tbl_Filter_TD_3685_output);
    gettimeofday(&tv_r_Filter_3_99_e, 0);

    struct timeval tv_r_Project_2_932_s, tv_r_Project_2_932_e;
    gettimeofday(&tv_r_Project_2_932_s, 0);
    SW_Project_TD_2822(tbl_SerializeFromObject_TD_4305_input, tbl_Project_TD_2822_output);
    gettimeofday(&tv_r_Project_2_932_e, 0);

    struct timeval tv_r_Project_2_974_s, tv_r_Project_2_974_e;
    gettimeofday(&tv_r_Project_2_974_s, 0);
    SW_Project_TD_2565(tbl_Filter_TD_3685_output, tbl_Project_TD_2565_output);
    gettimeofday(&tv_r_Project_2_974_e, 0);

    struct timeval tv_r_JOIN_INNER_1_571_s, tv_r_JOIN_INNER_1_571_e;
    gettimeofday(&tv_r_JOIN_INNER_1_571_s, 0);
    SW_JOIN_INNER_TD_141(tbl_Project_TD_2565_output, tbl_Project_TD_2822_output, tbl_JOIN_INNER_TD_141_output);
    gettimeofday(&tv_r_JOIN_INNER_1_571_e, 0);

    struct timeval tv_r_Aggregate_0_443_s, tv_r_Aggregate_0_443_e;
    gettimeofday(&tv_r_Aggregate_0_443_s, 0);
    SW_Aggregate_TD_0567(tbl_JOIN_INNER_TD_141_output, tbl_Aggregate_TD_0567_output);
    gettimeofday(&tv_r_Aggregate_0_443_e, 0);

    gettimeofday(&tv_r_e, 0); 
    // **************************** Print Execution Time ************************** // 
    std::cout << "Filter_3: " << tvdiff(&tv_r_Filter_3_99_s, &tv_r_Filter_3_99_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_4369_input: " << tbl_SerializeFromObject_TD_4369_input.getNumRow() << " " << std::endl; 

    std::cout << "Project_2: " << tvdiff(&tv_r_Project_2_932_s, &tv_r_Project_2_932_e) / 1000.0 << " ms " 
     << "tbl_SerializeFromObject_TD_4305_input: " << tbl_SerializeFromObject_TD_4305_input.getNumRow() << " " << std::endl; 

    std::cout << "Project_2: " << tvdiff(&tv_r_Project_2_974_s, &tv_r_Project_2_974_e) / 1000.0 << " ms " 
     << "tbl_Filter_TD_3685_output: " << tbl_Filter_TD_3685_output.getNumRow() << " " << std::endl; 

    std::cout << "JOIN_INNER_1: " << tvdiff(&tv_r_JOIN_INNER_1_571_s, &tv_r_JOIN_INNER_1_571_e) / 1000.0 << " ms " 
     << "tbl_Project_TD_2565_output: " << tbl_Project_TD_2565_output.getNumRow() << " " << "tbl_Project_TD_2822_output: " << tbl_Project_TD_2822_output.getNumRow() << " " << std::endl; 

    std::cout << "Aggregate_0: " << tvdiff(&tv_r_Aggregate_0_443_s, &tv_r_Aggregate_0_443_e) / 1000.0 << " ms " 
     << "tbl_JOIN_INNER_TD_141_output: " << tbl_JOIN_INNER_TD_141_output.getNumRow() << " " << std::endl; 

    std::cout << std::endl << " Total execution time: " << tvdiff(&tv_r_s, &tv_r_e) / 1000 << " ms"; 

    std::cout << std::endl << " Spark elapsed time: " << 0.43498862 * 1000 << "ms" << std::endl; 
    return 0; 
}
