#include <regex> 
#include <stdint.h> 

void SW_Filter_TD_7153(Table &tbl_SerializeFromObject_TD_8916_input, Table &tbl_Filter_TD_7153_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer((isnotnull(p_name#285) AND StartsWith(p_name#285, blush)))
    // Input: ListBuffer(p_partkey#284, p_name#285)
    // Output: ListBuffer(p_partkey#284)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_8916_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _p_name285 = tbl_SerializeFromObject_TD_8916_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
        if ((1) && (std::string(_p_name285.data()).find("blush")==0)) {
            int32_t _p_partkey284_t = tbl_SerializeFromObject_TD_8916_input.getInt32(i, 0);
            tbl_Filter_TD_7153_output.setInt32(r, 0, _p_partkey284_t);
            r++;
        }
    }
    tbl_Filter_TD_7153_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_7153_output #Row: " << tbl_Filter_TD_7153_output.getNumRow() << std::endl;
}

void SW_Filter_TD_760(Table &tbl_SerializeFromObject_TD_8615_input, Table &tbl_Filter_TD_760_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer(((l_shipdate#60 >= 19950101) AND (l_shipdate#60 < 19960101)))
    // Input: ListBuffer(l_partkey#51, l_suppkey#52, l_quantity#54, l_shipdate#60)
    // Output: ListBuffer(l_partkey#51, l_suppkey#52, l_quantity#54)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_8615_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _l_shipdate60 = tbl_SerializeFromObject_TD_8615_input.getInt32(i, 3);
        if ((_l_shipdate60 >= 19950101) && (_l_shipdate60 < 19960101)) {
            int32_t _l_partkey51_t = tbl_SerializeFromObject_TD_8615_input.getInt32(i, 0);
            tbl_Filter_TD_760_output.setInt32(r, 0, _l_partkey51_t);
            int32_t _l_suppkey52_t = tbl_SerializeFromObject_TD_8615_input.getInt32(i, 1);
            tbl_Filter_TD_760_output.setInt32(r, 1, _l_suppkey52_t);
            int32_t _l_quantity54_t = tbl_SerializeFromObject_TD_8615_input.getInt32(i, 2);
            tbl_Filter_TD_760_output.setInt32(r, 2, _l_quantity54_t);
            r++;
        }
    }
    tbl_Filter_TD_760_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_760_output #Row: " << tbl_Filter_TD_760_output.getNumRow() << std::endl;
}


void SW_Aggregate_TD_5342_consolidate(Table &tbl_Aggregate_TD_5342_output_preprocess, Table &tbl_Aggregate_TD_5342_output) {
    int nrow = 0;
    int nrow_p = tbl_Aggregate_TD_5342_output_preprocess.getNumRow();
    for (int r(0); r<nrow_p; ++r) {
        int32_t _suml_quantity2094 = tbl_Aggregate_TD_5342_output_preprocess.getInt32(r, 0);
        tbl_Aggregate_TD_5342_output.setInt32(r, 0, _suml_quantity2094);
        int32_t _l_partkey51 = tbl_Aggregate_TD_5342_output_preprocess.getInt32(r, 7);
        tbl_Aggregate_TD_5342_output.setInt32(r, 1, _l_partkey51);
        int32_t _l_suppkey52 = tbl_Aggregate_TD_5342_output_preprocess.getInt32(r, 6);
        tbl_Aggregate_TD_5342_output.setInt32(r, 2, _l_suppkey52);
    }
    nrow += nrow_p;
    tbl_Aggregate_TD_5342_output.setNumRow(nrow);
    std::cout << "tbl_Aggregate_TD_5342_output #Row: " << tbl_Aggregate_TD_5342_output.getNumRow() << std::endl;
}



void SW_Filter_TD_2767(Table &tbl_SerializeFromObject_TD_3798_input, Table &tbl_Filter_TD_2767_output) {
    // StringRowIDSubstitution: true StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer((isnotnull(n_name#165) AND (n_name#165 = INDONESIA)))
    // Input: ListBuffer(n_nationkey#164, n_name#165)
    // Output: ListBuffer(n_nationkey#164)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_3798_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _n_name165 = tbl_SerializeFromObject_TD_3798_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
        if ((1) && (std::string(_n_name165.data()) == "INDONESIA")) {
            int32_t _n_nationkey164_t = tbl_SerializeFromObject_TD_3798_input.getInt32(i, 0);
            tbl_Filter_TD_2767_output.setInt32(r, 0, _n_nationkey164_t);
            r++;
        }
    }
    tbl_Filter_TD_2767_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_2767_output #Row: " << tbl_Filter_TD_2767_output.getNumRow() << std::endl;
}



void SW_Sort_TD_0293(Table &tbl_JOIN_INNER_TD_1206_output, Table &tbl_SerializeFromObject_TD_3269_input, Table &tbl_SerializeFromObject_TD_3798_input, Table &tbl_Sort_TD_0293_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: true
    // Supported operation: Sort
    // Operation: ListBuffer(s_name#369 ASC NULLS FIRST)
    // Input: ListBuffer(s_name#369, s_address#370)
    // Output: ListBuffer(s_name#369, s_address#370)
    struct SW_Sort_TD_0293Row {
        std::string _s_name369;
        std::string _s_address370;
    }; 

    struct {
        bool operator()(const SW_Sort_TD_0293Row& a, const SW_Sort_TD_0293Row& b) const { return 
 (a._s_name369 < b._s_name369); 
}
    }SW_Sort_TD_0293_order; 

    int nrow1 = tbl_JOIN_INNER_TD_1206_output.getNumRow();
    std::vector<SW_Sort_TD_0293Row> rows;
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _s_name369 = tbl_SerializeFromObject_TD_3269_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(tbl_JOIN_INNER_TD_1206_output.getInt32(i, 0), 2);
        std::array<char, TPCH_READ_REGION_LEN + 1> _s_address370 = tbl_SerializeFromObject_TD_3269_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(tbl_JOIN_INNER_TD_1206_output.getInt32(i, 1), 2);
        SW_Sort_TD_0293Row t = {std::string(_s_name369.data()),std::string(_s_address370.data())};
        rows.push_back(t);
    }
    std::sort(rows.begin(), rows.end(), SW_Sort_TD_0293_order);
    int r = 0;
    for (auto& it : rows) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _s_name369{};
        memcpy(_s_name369.data(), (it._s_name369).data(), (it._s_name369).length());
        tbl_Sort_TD_0293_output.setcharN<char, TPCH_READ_REGION_LEN +1>(r, 0, _s_name369);
        std::array<char, TPCH_READ_REGION_LEN + 1> _s_address370{};
        memcpy(_s_address370.data(), (it._s_address370).data(), (it._s_address370).length());
        tbl_Sort_TD_0293_output.setcharN<char, TPCH_READ_REGION_LEN +1>(r, 1, _s_address370);
        if (r < 10) {
            std::cout << (it._s_name369).data() << " " << (it._s_address370).data() << " " << std::endl;
        }
        ++r;
    }
    tbl_Sort_TD_0293_output.setNumRow(r);
    std::cout << "tbl_Sort_TD_0293_output #Row: " << tbl_Sort_TD_0293_output.getNumRow() << std::endl;
}

