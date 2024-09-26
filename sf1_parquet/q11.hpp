#include <regex> 
#include <stdint.h> 

void SW_Filter_TD_4735(Table &tbl_SerializeFromObject_TD_5281_input, Table &tbl_Filter_TD_4735_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer((isnotnull(n_name#165) AND (n_name#165 = IRAN)))
    // Input: ListBuffer(n_nationkey#164, n_name#165)
    // Output: ListBuffer(n_nationkey#164)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_5281_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _n_name165 = tbl_SerializeFromObject_TD_5281_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
        if ((1) && (std::string(_n_name165.data()) == "IRAN")) {
            int32_t _n_nationkey164_t = tbl_SerializeFromObject_TD_5281_input.getInt32(i, 0);
            tbl_Filter_TD_4735_output.setInt32(r, 0, _n_nationkey164_t);
            r++;
        }
    }
    tbl_Filter_TD_4735_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_4735_output #Row: " << tbl_Filter_TD_4735_output.getNumRow() << std::endl;
}



void SW_Aggregate_TD_2846(Table &tbl_JOIN_INNER_TD_3355_output, Table &tbl_Aggregate_TD_2846_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Aggregate
    // Operation: ListBuffer(CheckOverflow((promote_precision(cast(cast(sum((ps_supplycost#332 * ps_availqty#331)) as decimal(20,0)) as decimal(30,10))) * 0.0001000000), DecimalType(31,10), true) AS (sum((ps_supplycost * ps_availqty)) * 0.0001000000)#1479)
    // Input: ListBuffer(ps_partkey#329, ps_availqty#331, ps_supplycost#332)
    // Output: ListBuffer((sum((ps_supplycost * ps_availqty)) * 0.0001000000)#1479)
    int64_t sum_0 = 0;
    int nrow1 = tbl_JOIN_INNER_TD_3355_output.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _ps_partkey329 = tbl_JOIN_INNER_TD_3355_output.getInt32(i, 0);
        int32_t _ps_availqty331 = tbl_JOIN_INNER_TD_3355_output.getInt32(i, 1);
        int32_t _ps_supplycost332 = tbl_JOIN_INNER_TD_3355_output.getInt32(i, 2);
        int64_t _000010000001479_sum_0 = (_ps_supplycost332 * _ps_availqty331);
        sum_0 += _000010000001479_sum_0;
    }
    int r = 0;
    int64_t _000010000001479 = (sum_0 * 0.0001000000);
    tbl_Aggregate_TD_2846_output.setInt64(r++, 0, _000010000001479);
    tbl_Aggregate_TD_2846_output.setNumRow(r);
    std::cout << "tbl_Aggregate_TD_2846_output #Row: " << tbl_Aggregate_TD_2846_output.getNumRow() << std::endl;
}

void SW_Aggregate_TD_2588_consolidate(Table &tbl_Aggregate_TD_2588_output_preprocess, Table &tbl_Aggregate_TD_2588_output) {
    int nrow = 0;
    int nrow_p = tbl_Aggregate_TD_2588_output_preprocess.getNumRow();
    for (int r(0); r<nrow_p; ++r) {
        int32_t _ps_partkey329 = tbl_Aggregate_TD_2588_output_preprocess.getInt32(r, 7);
        tbl_Aggregate_TD_2588_output.setInt32(r, 0, _ps_partkey329);
        int64_t _value1475L = tbl_Aggregate_TD_2588_output_preprocess.combineInt64(r, 8, 0);
        tbl_Aggregate_TD_2588_output.setInt64(r, 1, _value1475L);
    }
    nrow += nrow_p;
    tbl_Aggregate_TD_2588_output.setNumRow(nrow);
    std::cout << "tbl_Aggregate_TD_2588_output #Row: " << tbl_Aggregate_TD_2588_output.getNumRow() << std::endl;
}

void SW_Filter_TD_1992(Table &tbl_Aggregate_TD_2588_output, Table &tbl_Aggregate_TD_2846_output, Table &tbl_Filter_TD_1992_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer((isnotnull(value#1475L) AND (cast(cast(value#1475L as decimal(20,0)) as decimal(31,10)) > scalar-subquery#1476 [])))
    // Input: ListBuffer(ps_partkey#329, value#1475L)
    // Output: ListBuffer(ps_partkey#329, value#1475L)
    int r = 0;
    int nrow1 = tbl_Aggregate_TD_2588_output.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int64_t _value1475L = tbl_Aggregate_TD_2588_output.getInt64(i, 1);
        if ((1) && (_value1475L > tbl_Aggregate_TD_2846_output.getInt64(0, 0))) {
            int32_t _ps_partkey329_t = tbl_Aggregate_TD_2588_output.getInt32(i, 0);
            tbl_Filter_TD_1992_output.setInt32(r, 0, _ps_partkey329_t);
            int64_t _value1475L_t = tbl_Aggregate_TD_2588_output.getInt64(i, 1);
            tbl_Filter_TD_1992_output.setInt64(r, 1, _value1475L_t);
            r++;
        }
    }
    tbl_Filter_TD_1992_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_1992_output #Row: " << tbl_Filter_TD_1992_output.getNumRow() << std::endl;
}

void SW_Sort_TD_0896(Table &tbl_Filter_TD_1992_output, Table &tbl_Sort_TD_0896_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Sort
    // Operation: ListBuffer(value#1475L DESC NULLS LAST)
    // Input: ListBuffer(ps_partkey#329, value#1475L)
    // Output: ListBuffer(ps_partkey#329, value#1475L)
    struct SW_Sort_TD_0896Row {
        int32_t _ps_partkey329;
        int64_t _value1475L;
    }; 

    struct {
        bool operator()(const SW_Sort_TD_0896Row& a, const SW_Sort_TD_0896Row& b) const { return 
 (a._value1475L > b._value1475L); 
}
    }SW_Sort_TD_0896_order; 

    int nrow1 = tbl_Filter_TD_1992_output.getNumRow();
    std::vector<SW_Sort_TD_0896Row> rows;
    for (int i = 0; i < nrow1; i++) {
        int32_t _ps_partkey329 = tbl_Filter_TD_1992_output.getInt32(i, 0);
        int64_t _value1475L = tbl_Filter_TD_1992_output.getInt64(i, 1);
        SW_Sort_TD_0896Row t = {_ps_partkey329,_value1475L};
        rows.push_back(t);
    }
    std::sort(rows.begin(), rows.end(), SW_Sort_TD_0896_order);
    int r = 0;
    for (auto& it : rows) {
        tbl_Sort_TD_0896_output.setInt32(r, 0, it._ps_partkey329);
        tbl_Sort_TD_0896_output.setInt64(r, 1, it._value1475L);
        if (r < 10) {
            std::cout << it._ps_partkey329 << " " << it._value1475L << " " << std::endl;
        }
        ++r;
    }
    tbl_Sort_TD_0896_output.setNumRow(r);
    std::cout << "tbl_Sort_TD_0896_output #Row: " << tbl_Sort_TD_0896_output.getNumRow() << std::endl;
}

