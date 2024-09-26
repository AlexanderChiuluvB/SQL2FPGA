#include <regex> 
#include <stdint.h> 

void SW_Filter_TD_6867(Table &tbl_SerializeFromObject_TD_5637_input, Table &tbl_Filter_TD_6867_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer(((c_acctbal#130 > 0) AND substring(c_phone#129, 1, 2) IN (19,11,16,27,15,22,12)))
    // Input: ListBuffer(c_custkey#125, c_phone#129, c_acctbal#130)
    // Output: ListBuffer(c_acctbal#130)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_5637_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _c_acctbal130 = tbl_SerializeFromObject_TD_5637_input.getInt32(i, 2);
        std::array<char, TPCH_READ_REGION_LEN + 1> _c_phone129 = tbl_SerializeFromObject_TD_5637_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
        auto reuse_col_str_54 = std::string(_c_phone129.data()).substr(0, 2);
        if ((_c_acctbal130 > 0) && ((reuse_col_str_54 == "19") || (reuse_col_str_54 == "11") || (reuse_col_str_54 == "16") || (reuse_col_str_54 == "27") || (reuse_col_str_54 == "15") || (reuse_col_str_54 == "22") || (reuse_col_str_54 == "12") || (0))) {
            int32_t _c_acctbal130_t = tbl_SerializeFromObject_TD_5637_input.getInt32(i, 2);
            tbl_Filter_TD_6867_output.setInt32(r, 0, _c_acctbal130_t);
            r++;
        }
    }
    tbl_Filter_TD_6867_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_6867_output #Row: " << tbl_Filter_TD_6867_output.getNumRow() << std::endl;
}

void SW_Aggregate_TD_5939(Table &tbl_Filter_TD_6867_output, Table &tbl_Aggregate_TD_5939_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Aggregate
    // Operation: ListBuffer(avg(c_acctbal#130) AS avg(c_acctbal)#2285)
    // Input: ListBuffer(c_acctbal#130)
    // Output: ListBuffer(avg(c_acctbal)#2285)
    int64_t avg_0 = 0;
    int nrow1 = tbl_Filter_TD_6867_output.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _c_acctbal130 = tbl_Filter_TD_6867_output.getInt32(i, 0);
        int64_t _avgc_acctbal2285_avg_0 = _c_acctbal130;
        avg_0 = (avg_0 + _avgc_acctbal2285_avg_0);
    }
    int r = 0;
    int64_t _avgc_acctbal2285 = avg_0 / nrow1;
    tbl_Aggregate_TD_5939_output.setInt64(r++, 0, _avgc_acctbal2285);
    tbl_Aggregate_TD_5939_output.setNumRow(r);
    std::cout << "tbl_Aggregate_TD_5939_output #Row: " << tbl_Aggregate_TD_5939_output.getNumRow() << std::endl;
}

void SW_Filter_TD_4225(Table &tbl_SerializeFromObject_TD_5637_input, Table &tbl_Aggregate_TD_5939_output, Table &tbl_Filter_TD_4225_output) {
    // StringRowIDSubstitution: true StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer((substring(c_phone#129, 1, 2) IN (19,11,16,27,15,22,12) AND (cast(c_acctbal#130 as double) > scalar-subquery#2279 [])))
    // Input: ListBuffer(c_custkey#125, c_phone#129, c_acctbal#130)
    // Output: ListBuffer(c_custkey#125, c_phone#129, c_acctbal#130)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_5637_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _c_phone129 = tbl_SerializeFromObject_TD_5637_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
        int32_t _c_acctbal130 = tbl_SerializeFromObject_TD_5637_input.getInt32(i, 2);
        auto reuse_col_str_254 = std::string(_c_phone129.data()).substr(0, 2);
        if (((reuse_col_str_254 == "19") || (reuse_col_str_254 == "11") || (reuse_col_str_254 == "16") || (reuse_col_str_254 == "27") || (reuse_col_str_254 == "15") || (reuse_col_str_254 == "22") || (reuse_col_str_254 == "12") || (0)) && (_c_acctbal130 > tbl_Aggregate_TD_5939_output.getInt64(0, 0))) {
            int32_t _c_custkey125_t = tbl_SerializeFromObject_TD_5637_input.getInt32(i, 0);
            tbl_Filter_TD_4225_output.setInt32(r, 0, _c_custkey125_t);
            tbl_Filter_TD_4225_output.setInt32(r, 1, i);
            int32_t _c_acctbal130_t = tbl_SerializeFromObject_TD_5637_input.getInt32(i, 2);
            tbl_Filter_TD_4225_output.setInt32(r, 2, _c_acctbal130_t);
            r++;
        }
    }
    tbl_Filter_TD_4225_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_4225_output #Row: " << tbl_Filter_TD_4225_output.getNumRow() << std::endl;
}


void SW_Project_TD_2797(Table &tbl_JOIN_LEFTANTI_TD_3172_output, Table &tbl_SerializeFromObject_TD_5637_input, Table &tbl_Project_TD_2797_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: true
    // Supported operation: Project
    // Operation: ListBuffer(substring(c_phone#129, 1, 2) AS cntrycode#2278)
    // Input: ListBuffer(c_phone#129, c_acctbal#130)
    // Output: ListBuffer(cntrycode#2278, c_acctbal#130)
    int nrow1 = tbl_JOIN_LEFTANTI_TD_3172_output.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _c_phone129 = tbl_SerializeFromObject_TD_5637_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(tbl_JOIN_LEFTANTI_TD_3172_output.getInt32(i, 0), 1);
        int32_t _c_acctbal130 = tbl_JOIN_LEFTANTI_TD_3172_output.getInt32(i, 1);
        std::string _cntrycode2278_str = std::string(_c_phone129.data()).substr(0, 2);
        std::array<char, TPCH_READ_REGION_LEN + 1> _cntrycode2278{};
        memcpy(_cntrycode2278.data(), _cntrycode2278_str.data(), (_cntrycode2278_str).length());
        tbl_Project_TD_2797_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(i, 0, _cntrycode2278);
        tbl_Project_TD_2797_output.setInt32(i, 1, _c_acctbal130);
    }
    tbl_Project_TD_2797_output.setNumRow(nrow1);
    std::cout << "tbl_Project_TD_2797_output #Row: " << tbl_Project_TD_2797_output.getNumRow() << std::endl;
}

typedef std::string SW_Aggregate_TD_1738_key;
struct SW_Aggregate_TD_1738_payload {
    int64_t _numcust2281L_count_0;
    int64_t _totacctbal2282L_sum_1;
};
void SW_Aggregate_TD_1738(Table &tbl_Project_TD_2797_output, Table &tbl_Aggregate_TD_1738_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Aggregate
    // Operation: ListBuffer(cntrycode#2278, count(1) AS numcust#2281L, sum(c_acctbal#130) AS totacctbal#2282L)
    // Input: ListBuffer(cntrycode#2278, c_acctbal#130)
    // Output: ListBuffer(cntrycode#2278, numcust#2281L, totacctbal#2282L)
    std::unordered_map<SW_Aggregate_TD_1738_key, SW_Aggregate_TD_1738_payload> ht1;
    int nrow1 = tbl_Project_TD_2797_output.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _cntrycode2278 = tbl_Project_TD_2797_output.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 0);
        int32_t _c_acctbal130 = tbl_Project_TD_2797_output.getInt32(i, 1);
        SW_Aggregate_TD_1738_key k = std::string(_cntrycode2278.data());
        int64_t _numcust2281L_count_0 = 1 != 0 ? 1 : 0;
        int64_t _totacctbal2282L_sum_1 = _c_acctbal130;
        SW_Aggregate_TD_1738_payload p{_numcust2281L_count_0, _totacctbal2282L_sum_1};
        auto it = ht1.find(k);
        if (it != ht1.end()) {
            int64_t count_0 = (it->second)._numcust2281L_count_0 + _numcust2281L_count_0;
            p._numcust2281L_count_0 = count_0;
            int64_t sum_1 = (it->second)._totacctbal2282L_sum_1 + _totacctbal2282L_sum_1;
            p._totacctbal2282L_sum_1 = sum_1;
            ht1[k] = p;
        } else { 
            ht1.insert(std::make_pair(k, p));
        }
    }
    int r = 0;
    for (auto& it : ht1) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _cntrycode2278{};
        memcpy(_cntrycode2278.data(), (it.first).data(), (it.first).length());
        tbl_Aggregate_TD_1738_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(r, 0, _cntrycode2278);
        int64_t _numcust2281L = (it.second)._numcust2281L_count_0;
        tbl_Aggregate_TD_1738_output.setInt64(r, 1, _numcust2281L);
        int64_t _totacctbal2282L = (it.second)._totacctbal2282L_sum_1;
        tbl_Aggregate_TD_1738_output.setInt64(r, 2, _totacctbal2282L);
        ++r;
    }
    tbl_Aggregate_TD_1738_output.setNumRow(r);
    std::cout << "tbl_Aggregate_TD_1738_output #Row: " << tbl_Aggregate_TD_1738_output.getNumRow() << std::endl;
}

void SW_Sort_TD_0919(Table &tbl_Aggregate_TD_1738_output, Table &tbl_Sort_TD_0919_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Sort
    // Operation: ListBuffer(cntrycode#2278 ASC NULLS FIRST)
    // Input: ListBuffer(cntrycode#2278, numcust#2281L, totacctbal#2282L)
    // Output: ListBuffer(cntrycode#2278, numcust#2281L, totacctbal#2282L)
    struct SW_Sort_TD_0919Row {
        std::string _cntrycode2278;
        int64_t _numcust2281L;
        int64_t _totacctbal2282L;
    }; 

    struct {
        bool operator()(const SW_Sort_TD_0919Row& a, const SW_Sort_TD_0919Row& b) const { return 
 (a._cntrycode2278 < b._cntrycode2278); 
}
    }SW_Sort_TD_0919_order; 

    int nrow1 = tbl_Aggregate_TD_1738_output.getNumRow();
    std::vector<SW_Sort_TD_0919Row> rows;
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _cntrycode2278 = tbl_Aggregate_TD_1738_output.getcharN<char, TPCH_READ_REGION_LEN +1>(i, 0);
        int64_t _numcust2281L = tbl_Aggregate_TD_1738_output.getInt64(i, 1);
        int64_t _totacctbal2282L = tbl_Aggregate_TD_1738_output.getInt64(i, 2);
        SW_Sort_TD_0919Row t = {std::string(_cntrycode2278.data()),_numcust2281L,_totacctbal2282L};
        rows.push_back(t);
    }
    std::sort(rows.begin(), rows.end(), SW_Sort_TD_0919_order);
    int r = 0;
    for (auto& it : rows) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _cntrycode2278{};
        memcpy(_cntrycode2278.data(), (it._cntrycode2278).data(), (it._cntrycode2278).length());
        tbl_Sort_TD_0919_output.setcharN<char, TPCH_READ_REGION_LEN +1>(r, 0, _cntrycode2278);
        tbl_Sort_TD_0919_output.setInt64(r, 1, it._numcust2281L);
        tbl_Sort_TD_0919_output.setInt64(r, 2, it._totacctbal2282L);
        if (r < 10) {
            std::cout << (it._cntrycode2278).data() << " " << it._numcust2281L << " " << it._totacctbal2282L << " " << std::endl;
        }
        ++r;
    }
    tbl_Sort_TD_0919_output.setNumRow(r);
    std::cout << "tbl_Sort_TD_0919_output #Row: " << tbl_Sort_TD_0919_output.getNumRow() << std::endl;
}

