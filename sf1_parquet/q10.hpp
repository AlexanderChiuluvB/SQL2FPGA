#include <regex> 
#include <stdint.h> 

void SW_Filter_TD_555(Table &tbl_SerializeFromObject_TD_6957_input, Table &tbl_Filter_TD_555_output) {
    // StringRowIDSubstitution: true StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer(((o_orderdate#231 >= 19940801) AND (o_orderdate#231 < 19941101)))
    // Input: ListBuffer(o_orderkey#227, o_custkey#228, o_orderdate#231)
    // Output: ListBuffer(o_orderkey#227, o_custkey#228)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_6957_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _o_orderdate231 = tbl_SerializeFromObject_TD_6957_input.getInt32(i, 2);
        if ((_o_orderdate231 >= 19940801) && (_o_orderdate231 < 19941101)) {
            int32_t _o_orderkey227_t = tbl_SerializeFromObject_TD_6957_input.getInt32(i, 0);
            tbl_Filter_TD_555_output.setInt32(r, 0, _o_orderkey227_t);
            int32_t _o_custkey228_t = tbl_SerializeFromObject_TD_6957_input.getInt32(i, 1);
            tbl_Filter_TD_555_output.setInt32(r, 1, _o_custkey228_t);
            r++;
        }
    }
    tbl_Filter_TD_555_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_555_output #Row: " << tbl_Filter_TD_555_output.getNumRow() << std::endl;
}

void SW_Filter_TD_4263(Table &tbl_SerializeFromObject_TD_5430_input, Table &tbl_Filter_TD_4263_output) {
    // StringRowIDSubstitution: true StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer((l_returnflag#58 = 82))
    // Input: ListBuffer(l_orderkey#50, l_extendedprice#55, l_discount#56, l_returnflag#58)
    // Output: ListBuffer(l_orderkey#50, l_extendedprice#55, l_discount#56)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_5430_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _l_returnflag58 = tbl_SerializeFromObject_TD_5430_input.getInt32(i, 3);
        if (_l_returnflag58 == 82) {
            int32_t _l_orderkey50_t = tbl_SerializeFromObject_TD_5430_input.getInt32(i, 0);
            tbl_Filter_TD_4263_output.setInt32(r, 0, _l_orderkey50_t);
            int32_t _l_extendedprice55_t = tbl_SerializeFromObject_TD_5430_input.getInt32(i, 1);
            tbl_Filter_TD_4263_output.setInt32(r, 1, _l_extendedprice55_t);
            int32_t _l_discount56_t = tbl_SerializeFromObject_TD_5430_input.getInt32(i, 2);
            tbl_Filter_TD_4263_output.setInt32(r, 2, _l_discount56_t);
            r++;
        }
    }
    tbl_Filter_TD_4263_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_4263_output #Row: " << tbl_Filter_TD_4263_output.getNumRow() << std::endl;
}




struct SW_Aggregate_TD_1445_key {
    int32_t _c_custkey125;
    std::string _c_name126;
    int32_t _c_acctbal130;
    std::string _n_name165;
    bool operator==(const SW_Aggregate_TD_1445_key& other) const { return (_c_custkey125 == other._c_custkey125) && (_c_name126 == other._c_name126) && (_c_acctbal130 == other._c_acctbal130) && (_n_name165 == other._n_name165); }
};
namespace std {
template <>
struct hash<SW_Aggregate_TD_1445_key> {
    std::size_t operator() (const SW_Aggregate_TD_1445_key& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<int32_t>()(k._c_custkey125)) + (hash<string>()(k._c_name126)) + (hash<int32_t>()(k._c_acctbal130)) + (hash<string>()(k._n_name165));
    }
};
}
struct SW_Aggregate_TD_1445_payload {
    int64_t _revenue1411L_sum_0;
};
void SW_Aggregate_TD_1445(Table &tbl_JOIN_INNER_TD_2546_output, Table &tbl_SerializeFromObject_TD_5424_input, Table &tbl_SerializeFromObject_TD_6957_input, Table &tbl_SerializeFromObject_TD_5430_input, Table &tbl_SerializeFromObject_TD_3408_input, Table &tbl_Aggregate_TD_1445_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: true
    // Supported operation: Aggregate
    // Operation: ListBuffer(c_custkey#125, c_name#126, c_acctbal#130, n_name#165, sum((l_extendedprice#55 * (100 - l_discount#56))) AS revenue#1411L)
    // Input: ListBuffer(c_custkey#125, c_name#126, c_acctbal#130, l_extendedprice#55, l_discount#56, n_name#165)
    // Output: ListBuffer(c_custkey#125, c_name#126, revenue#1411L, c_acctbal#130, n_name#165)
    std::unordered_map<SW_Aggregate_TD_1445_key, SW_Aggregate_TD_1445_payload> ht1;
    int nrow1 = tbl_JOIN_INNER_TD_2546_output.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _c_custkey125 = tbl_JOIN_INNER_TD_2546_output.getInt32(i, 0);
        std::array<char, TPCH_READ_REGION_LEN + 1> _c_name126 = tbl_SerializeFromObject_TD_5424_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(tbl_JOIN_INNER_TD_2546_output.getInt32(i, 1), 1);
        int32_t _c_acctbal130 = tbl_JOIN_INNER_TD_2546_output.getInt32(i, 2);
        int32_t _l_extendedprice55 = tbl_JOIN_INNER_TD_2546_output.getInt32(i, 3);
        int32_t _l_discount56 = tbl_JOIN_INNER_TD_2546_output.getInt32(i, 4);
        std::array<char, TPCH_READ_REGION_LEN + 1> _n_name165 = tbl_SerializeFromObject_TD_3408_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(tbl_JOIN_INNER_TD_2546_output.getInt32(i, 5), 1);
        SW_Aggregate_TD_1445_key k{_c_custkey125, std::string(_c_name126.data()), _c_acctbal130, std::string(_n_name165.data())};
        int64_t _revenue1411L_sum_0 = (_l_extendedprice55 * (100 - _l_discount56));
        SW_Aggregate_TD_1445_payload p{_revenue1411L_sum_0};
        auto it = ht1.find(k);
        if (it != ht1.end()) {
            int64_t sum_0 = (it->second)._revenue1411L_sum_0 + _revenue1411L_sum_0;
            p._revenue1411L_sum_0 = sum_0;
            ht1[k] = p;
        } else { 
            ht1.insert(std::make_pair(k, p));
        }
    }
    int r = 0;
    for (auto& it : ht1) {
        tbl_Aggregate_TD_1445_output.setInt32(r, 0, (it.first)._c_custkey125);
        std::array<char, TPCH_READ_REGION_LEN + 1> _c_name126{};
        memcpy(_c_name126.data(), ((it.first)._c_name126).data(), ((it.first)._c_name126).length());
        tbl_Aggregate_TD_1445_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(r, 1, _c_name126);
        tbl_Aggregate_TD_1445_output.setInt32(r, 3, (it.first)._c_acctbal130);
        std::array<char, TPCH_READ_REGION_LEN + 1> _n_name165{};
        memcpy(_n_name165.data(), ((it.first)._n_name165).data(), ((it.first)._n_name165).length());
        tbl_Aggregate_TD_1445_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(r, 4, _n_name165);
        int64_t _revenue1411L = (it.second)._revenue1411L_sum_0;
        tbl_Aggregate_TD_1445_output.setInt64(r, 2, _revenue1411L);
        ++r;
    }
    tbl_Aggregate_TD_1445_output.setNumRow(r);
    std::cout << "tbl_Aggregate_TD_1445_output #Row: " << tbl_Aggregate_TD_1445_output.getNumRow() << std::endl;
}

void SW_Sort_TD_0873(Table &tbl_Aggregate_TD_1445_output, Table &tbl_Sort_TD_0873_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Sort
    // Operation: ListBuffer(revenue#1411L DESC NULLS LAST)
    // Input: ListBuffer(c_custkey#125, c_name#126, revenue#1411L, c_acctbal#130, n_name#165)
    // Output: ListBuffer(c_custkey#125, c_name#126, revenue#1411L, c_acctbal#130, n_name#165)
    struct SW_Sort_TD_0873Row {
        int32_t _c_custkey125;
        std::string _c_name126;
        int64_t _revenue1411L;
        int32_t _c_acctbal130;
        std::string _n_name165;
    }; 

    struct {
        bool operator()(const SW_Sort_TD_0873Row& a, const SW_Sort_TD_0873Row& b) const { return 
 (a._revenue1411L > b._revenue1411L); 
}
    }SW_Sort_TD_0873_order; 

    int nrow1 = tbl_Aggregate_TD_1445_output.getNumRow();
    std::vector<SW_Sort_TD_0873Row> rows;
    for (int i = 0; i < nrow1; i++) {
        int32_t _c_custkey125 = tbl_Aggregate_TD_1445_output.getInt32(i, 0);
        std::array<char, TPCH_READ_REGION_LEN + 1> _c_name126 = tbl_Aggregate_TD_1445_output.getcharN<char, TPCH_READ_REGION_LEN +1>(i, 1);
        int64_t _revenue1411L = tbl_Aggregate_TD_1445_output.getInt64(i, 2);
        int32_t _c_acctbal130 = tbl_Aggregate_TD_1445_output.getInt32(i, 3);
        std::array<char, TPCH_READ_REGION_LEN + 1> _n_name165 = tbl_Aggregate_TD_1445_output.getcharN<char, TPCH_READ_REGION_LEN +1>(i, 4);
        SW_Sort_TD_0873Row t = {_c_custkey125,std::string(_c_name126.data()),_revenue1411L,_c_acctbal130,std::string(_n_name165.data())};
        rows.push_back(t);
    }
    std::sort(rows.begin(), rows.end(), SW_Sort_TD_0873_order);
    int r = 0;
    for (auto& it : rows) {
        tbl_Sort_TD_0873_output.setInt32(r, 0, it._c_custkey125);
        std::array<char, TPCH_READ_REGION_LEN + 1> _c_name126{};
        memcpy(_c_name126.data(), (it._c_name126).data(), (it._c_name126).length());
        tbl_Sort_TD_0873_output.setcharN<char, TPCH_READ_REGION_LEN +1>(r, 1, _c_name126);
        tbl_Sort_TD_0873_output.setInt64(r, 2, it._revenue1411L);
        tbl_Sort_TD_0873_output.setInt32(r, 3, it._c_acctbal130);
        std::array<char, TPCH_READ_REGION_LEN + 1> _n_name165{};
        memcpy(_n_name165.data(), (it._n_name165).data(), (it._n_name165).length());
        tbl_Sort_TD_0873_output.setcharN<char, TPCH_READ_REGION_LEN +1>(r, 4, _n_name165);
        if (r < 10) {
            std::cout << it._c_custkey125 << " " << (it._c_name126).data() << " " << it._revenue1411L << " " << it._c_acctbal130 << " " << (it._n_name165).data() << " " << std::endl;
        }
        ++r;
    }
    tbl_Sort_TD_0873_output.setNumRow(r);
    std::cout << "tbl_Sort_TD_0873_output #Row: " << tbl_Sort_TD_0873_output.getNumRow() << std::endl;
}

