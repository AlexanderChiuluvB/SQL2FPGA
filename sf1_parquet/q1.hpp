#include <regex> 
#include <stdint.h> 

void SW_Filter_TD_2759(Table &tbl_SerializeFromObject_TD_3487_input, Table &tbl_Filter_TD_2759_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer((l_shipdate#60 <= 19980803))
    // Input: ListBuffer(l_quantity#54, l_extendedprice#55, l_discount#56, l_tax#57, l_returnflag#58, l_linestatus#59, l_shipdate#60)
    // Output: ListBuffer(l_quantity#54, l_extendedprice#55, l_discount#56, l_tax#57, l_returnflag#58, l_linestatus#59)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_3487_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _l_shipdate60 = tbl_SerializeFromObject_TD_3487_input.getInt32(i, 6);
        if (_l_shipdate60 <= 19980803) {
            int32_t _l_quantity54_t = tbl_SerializeFromObject_TD_3487_input.getInt32(i, 0);
            tbl_Filter_TD_2759_output.setInt32(r, 0, _l_quantity54_t);
            int32_t _l_extendedprice55_t = tbl_SerializeFromObject_TD_3487_input.getInt32(i, 1);
            tbl_Filter_TD_2759_output.setInt32(r, 1, _l_extendedprice55_t);
            int32_t _l_discount56_t = tbl_SerializeFromObject_TD_3487_input.getInt32(i, 2);
            tbl_Filter_TD_2759_output.setInt32(r, 2, _l_discount56_t);
            int32_t _l_tax57_t = tbl_SerializeFromObject_TD_3487_input.getInt32(i, 3);
            tbl_Filter_TD_2759_output.setInt32(r, 3, _l_tax57_t);
            int32_t _l_returnflag58_t = tbl_SerializeFromObject_TD_3487_input.getInt32(i, 4);
            tbl_Filter_TD_2759_output.setInt32(r, 4, _l_returnflag58_t);
            int32_t _l_linestatus59_t = tbl_SerializeFromObject_TD_3487_input.getInt32(i, 5);
            tbl_Filter_TD_2759_output.setInt32(r, 5, _l_linestatus59_t);
            r++;
        }
    }
    tbl_Filter_TD_2759_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_2759_output #Row: " << tbl_Filter_TD_2759_output.getNumRow() << std::endl;
}

void SW_Aggregate_TD_1416_consolidate(Table &tbl_Aggregate_TD_1416_output_preprocess, Table &tbl_Aggregate_TD_1416_output) {
    int nrow = 0;
    int nrow_p = tbl_Aggregate_TD_1416_output_preprocess.getNumRow();
    for (int r(0); r<nrow_p; ++r) {
        int32_t _l_returnflag58 = tbl_Aggregate_TD_1416_output_preprocess.getInt32(r, 7);
        tbl_Aggregate_TD_1416_output.setInt32(r, 0, _l_returnflag58);
        int32_t _l_linestatus59 = tbl_Aggregate_TD_1416_output_preprocess.getInt32(r, 6);
        tbl_Aggregate_TD_1416_output.setInt32(r, 1, _l_linestatus59);
        int64_t _sum_qty743L = tbl_Aggregate_TD_1416_output_preprocess.combineInt64(r, 8, 0);
        tbl_Aggregate_TD_1416_output.setInt64(r, 2, _sum_qty743L);
        int64_t _sum_base_price744L = tbl_Aggregate_TD_1416_output_preprocess.combineInt64(r, 9, 1);
        tbl_Aggregate_TD_1416_output.setInt64(r, 3, _sum_base_price744L);
        int64_t _sum_disc_price745L = tbl_Aggregate_TD_1416_output_preprocess.combineInt64(r, 10, 2);
        tbl_Aggregate_TD_1416_output.setInt64(r, 4, _sum_disc_price745L);
        int64_t _sum_charge746L = tbl_Aggregate_TD_1416_output_preprocess.combineInt64(r, 11, 3);
        tbl_Aggregate_TD_1416_output.setInt64(r, 5, _sum_charge746L);
        int32_t _avg_qty747 = tbl_Aggregate_TD_1416_output_preprocess.getInt32(r, 4);
        tbl_Aggregate_TD_1416_output.setInt32(r, 6, _avg_qty747);
        int32_t _avg_price748 = tbl_Aggregate_TD_1416_output_preprocess.getInt32(r, 5);
        tbl_Aggregate_TD_1416_output.setInt32(r, 7, _avg_price748);
        int32_t _avg_disc749 = tbl_Aggregate_TD_1416_output_preprocess.getInt32(r, 6);
        tbl_Aggregate_TD_1416_output.setInt32(r, 8, _avg_disc749);
        int32_t _count_order750L = tbl_Aggregate_TD_1416_output_preprocess.getInt32(r, 7);
        tbl_Aggregate_TD_1416_output.setInt32(r, 9, _count_order750L);
    }
    nrow += nrow_p;
    tbl_Aggregate_TD_1416_output.setNumRow(nrow);
    std::cout << "tbl_Aggregate_TD_1416_output #Row: " << tbl_Aggregate_TD_1416_output.getNumRow() << std::endl;
}

void SW_Sort_TD_0930(Table &tbl_Aggregate_TD_1416_output, Table &tbl_Sort_TD_0930_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Sort
    // Operation: ListBuffer(l_returnflag#58 ASC NULLS FIRST, l_linestatus#59 ASC NULLS FIRST)
    // Input: ListBuffer(l_returnflag#58, l_linestatus#59, sum_qty#743L, sum_base_price#744L, sum_disc_price#745L, sum_charge#746L, avg_qty#747, avg_price#748, avg_disc#749, count_order#750L)
    // Output: ListBuffer(l_returnflag#58, l_linestatus#59, sum_qty#743L, sum_base_price#744L, sum_disc_price#745L, sum_charge#746L, avg_qty#747, avg_price#748, avg_disc#749, count_order#750L)
    struct SW_Sort_TD_0930Row {
        int32_t _l_returnflag58;
        int32_t _l_linestatus59;
        int64_t _sum_qty743L;
        int64_t _sum_base_price744L;
        int64_t _sum_disc_price745L;
        int64_t _sum_charge746L;
        int32_t _avg_qty747;
        int32_t _avg_price748;
        int32_t _avg_disc749;
        int64_t _count_order750L;
    }; 

    struct {
        bool operator()(const SW_Sort_TD_0930Row& a, const SW_Sort_TD_0930Row& b) const { return 
 (a._l_returnflag58 < b._l_returnflag58) || 
 ((a._l_returnflag58 == b._l_returnflag58) && (a._l_linestatus59 < b._l_linestatus59)); 
}
    }SW_Sort_TD_0930_order; 

    int nrow1 = tbl_Aggregate_TD_1416_output.getNumRow();
    std::vector<SW_Sort_TD_0930Row> rows;
    for (int i = 0; i < nrow1; i++) {
        int32_t _l_returnflag58 = tbl_Aggregate_TD_1416_output.getInt32(i, 0);
        int32_t _l_linestatus59 = tbl_Aggregate_TD_1416_output.getInt32(i, 1);
        int64_t _sum_qty743L = tbl_Aggregate_TD_1416_output.getInt64(i, 2);
        int64_t _sum_base_price744L = tbl_Aggregate_TD_1416_output.getInt64(i, 3);
        int64_t _sum_disc_price745L = tbl_Aggregate_TD_1416_output.getInt64(i, 4);
        int64_t _sum_charge746L = tbl_Aggregate_TD_1416_output.getInt64(i, 5);
        int32_t _avg_qty747 = tbl_Aggregate_TD_1416_output.getInt32(i, 6);
        int32_t _avg_price748 = tbl_Aggregate_TD_1416_output.getInt32(i, 7);
        int32_t _avg_disc749 = tbl_Aggregate_TD_1416_output.getInt32(i, 8);
        int64_t _count_order750L = tbl_Aggregate_TD_1416_output.getInt64(i, 9);
        SW_Sort_TD_0930Row t = {_l_returnflag58,_l_linestatus59,_sum_qty743L,_sum_base_price744L,_sum_disc_price745L,_sum_charge746L,_avg_qty747,_avg_price748,_avg_disc749,_count_order750L};
        rows.push_back(t);
    }
    std::sort(rows.begin(), rows.end(), SW_Sort_TD_0930_order);
    int r = 0;
    for (auto& it : rows) {
        tbl_Sort_TD_0930_output.setInt32(r, 0, it._l_returnflag58);
        tbl_Sort_TD_0930_output.setInt32(r, 1, it._l_linestatus59);
        tbl_Sort_TD_0930_output.setInt64(r, 2, it._sum_qty743L);
        tbl_Sort_TD_0930_output.setInt64(r, 3, it._sum_base_price744L);
        tbl_Sort_TD_0930_output.setInt64(r, 4, it._sum_disc_price745L);
        tbl_Sort_TD_0930_output.setInt64(r, 5, it._sum_charge746L);
        tbl_Sort_TD_0930_output.setInt32(r, 6, it._avg_qty747);
        tbl_Sort_TD_0930_output.setInt32(r, 7, it._avg_price748);
        tbl_Sort_TD_0930_output.setInt32(r, 8, it._avg_disc749);
        tbl_Sort_TD_0930_output.setInt64(r, 9, it._count_order750L);
        if (r < 10) {
            std::cout << it._l_returnflag58 << " " << it._l_linestatus59 << " " << it._sum_qty743L << " " << it._sum_base_price744L << " " << it._sum_disc_price745L << " " << it._sum_charge746L << " " << it._avg_qty747 << " " << it._avg_price748 << " " << it._avg_disc749 << " " << it._count_order750L << " " << std::endl;
        }
        ++r;
    }
    tbl_Sort_TD_0930_output.setNumRow(r);
    std::cout << "tbl_Sort_TD_0930_output #Row: " << tbl_Sort_TD_0930_output.getNumRow() << std::endl;
}

