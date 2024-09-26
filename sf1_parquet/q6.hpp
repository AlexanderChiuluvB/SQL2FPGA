#include <regex> 
#include <stdint.h> 

void SW_Filter_TD_1598(Table &tbl_SerializeFromObject_TD_2959_input, Table &tbl_Filter_TD_1598_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer((((l_shipdate#60 >= 19940101) AND (l_shipdate#60 < 19950101)) AND (((l_discount#56 >= 5) AND (l_discount#56 <= 7)) AND (l_quantity#54 < 24))))
    // Input: ListBuffer(l_extendedprice#55, l_discount#56, l_shipdate#60, l_quantity#54)
    // Output: ListBuffer(l_extendedprice#55, l_discount#56)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_2959_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _l_shipdate60 = tbl_SerializeFromObject_TD_2959_input.getInt32(i, 2);
        int32_t _l_discount56 = tbl_SerializeFromObject_TD_2959_input.getInt32(i, 1);
        int32_t _l_quantity54 = tbl_SerializeFromObject_TD_2959_input.getInt32(i, 3);
        if (((_l_shipdate60 >= 19940101) && (_l_shipdate60 < 19950101)) && (((_l_discount56 >= 5) && (_l_discount56 <= 7)) && (_l_quantity54 < 24))) {
            int32_t _l_extendedprice55_t = tbl_SerializeFromObject_TD_2959_input.getInt32(i, 0);
            tbl_Filter_TD_1598_output.setInt32(r, 0, _l_extendedprice55_t);
            int32_t _l_discount56_t = tbl_SerializeFromObject_TD_2959_input.getInt32(i, 1);
            tbl_Filter_TD_1598_output.setInt32(r, 1, _l_discount56_t);
            r++;
        }
    }
    tbl_Filter_TD_1598_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_1598_output #Row: " << tbl_Filter_TD_1598_output.getNumRow() << std::endl;
}

void SW_Aggregate_TD_0144(Table &tbl_Filter_TD_1598_output, Table &tbl_Aggregate_TD_0144_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Aggregate
    // Operation: ListBuffer(sum((l_extendedprice#55 * l_discount#56)) AS revenue#1171L)
    // Input: ListBuffer(l_extendedprice#55, l_discount#56)
    // Output: ListBuffer(revenue#1171L)
    int64_t sum_0 = 0;
    int nrow1 = tbl_Filter_TD_1598_output.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _l_extendedprice55 = tbl_Filter_TD_1598_output.getInt32(i, 0);
        int32_t _l_discount56 = tbl_Filter_TD_1598_output.getInt32(i, 1);
        int64_t _revenue1171L_sum_0 = (_l_extendedprice55 * _l_discount56);
        sum_0 += _revenue1171L_sum_0;
    }
    int r = 0;
    int64_t _revenue1171L = sum_0;
    tbl_Aggregate_TD_0144_output.setInt64(r++, 0, _revenue1171L);
    tbl_Aggregate_TD_0144_output.setNumRow(r);
    std::cout << "tbl_Aggregate_TD_0144_output #Row: " << tbl_Aggregate_TD_0144_output.getNumRow() << std::endl;
}

