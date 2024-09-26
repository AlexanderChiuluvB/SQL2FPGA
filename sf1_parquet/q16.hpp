#include <regex> 
#include <stdint.h> 

void SW_Filter_TD_4335(Table &tbl_SerializeFromObject_TD_596_input, Table &tbl_Filter_TD_4335_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer((isnotnull(s_comment#374) AND s_comment#374 LIKE %Customer%Complaints%))
    // Input: ListBuffer(s_suppkey#368, s_comment#374)
    // Output: ListBuffer(s_suppkey#368)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_596_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _s_comment374 = tbl_SerializeFromObject_TD_596_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
        struct custom_func {
                bool strm_pattern(std::string sub1, std::string sub2, std::string s, int len = 7) {
                    std::string::size_type spe_f = s.find(sub1);
                    std::string::size_type c_f = 0;
                    while (spe_f != std::string::npos) {
                        c_f += (spe_f + len);
                        std::string sub_s = s.substr(c_f);
                        if (sub_s.find(sub2) != std::string::npos) return true;
                        spe_f = sub_s.find(sub1);
                    }
                    return false;
                }
        }custom_func_obj;
        if ((1) && custom_func_obj.strm_pattern("Customer", "Complaints", _s_comment374.data())) {
            int32_t _s_suppkey368_t = tbl_SerializeFromObject_TD_596_input.getInt32(i, 0);
            tbl_Filter_TD_4335_output.setInt32(r, 0, _s_suppkey368_t);
            r++;
        }
    }
    tbl_Filter_TD_4335_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_4335_output #Row: " << tbl_Filter_TD_4335_output.getNumRow() << std::endl;
}

void SW_Filter_TD_3859(Table &tbl_SerializeFromObject_TD_4698_input, Table &tbl_Filter_TD_3859_output) {
    // StringRowIDSubstitution: true StringRowIDBackSubstitution: false
    // Supported operation: Filter
    // Operation: ListBuffer(((isnotnull(p_brand#287) AND isnotnull(p_type#288)) AND ((NOT (p_brand#287 = Brand#32) AND NOT StartsWith(p_type#288, SMALL ANODIZED)) AND p_size#289 IN (43,7,27,21,5,15,36,11))))
    // Input: ListBuffer(p_partkey#284, p_brand#287, p_type#288, p_size#289)
    // Output: ListBuffer(p_partkey#284, p_brand#287, p_type#288, p_size#289)
    int r = 0;
    int nrow1 = tbl_SerializeFromObject_TD_4698_input.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _p_brand287 = tbl_SerializeFromObject_TD_4698_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 1);
        std::array<char, TPCH_READ_REGION_LEN + 1> _p_type288 = tbl_SerializeFromObject_TD_4698_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(i, 2);
        int32_t _p_size289 = tbl_SerializeFromObject_TD_4698_input.getInt32(i, 3);
        auto reuse_col_str_711 = _p_size289;
        if (((1) && (1)) && ((!((std::string(_p_brand287.data()) == "Brand#32")) && !((std::string(_p_type288.data()).find("SMALL ANODIZED")==0))) && ((reuse_col_str_711 == 43) || (reuse_col_str_711 == 7) || (reuse_col_str_711 == 27) || (reuse_col_str_711 == 21) || (reuse_col_str_711 == 5) || (reuse_col_str_711 == 15) || (reuse_col_str_711 == 36) || (reuse_col_str_711 == 11) || (0)))) {
            int32_t _p_partkey284_t = tbl_SerializeFromObject_TD_4698_input.getInt32(i, 0);
            tbl_Filter_TD_3859_output.setInt32(r, 0, _p_partkey284_t);
            tbl_Filter_TD_3859_output.setInt32(r, 1, i);
            tbl_Filter_TD_3859_output.setInt32(r, 2, i);
            int32_t _p_size289_t = tbl_SerializeFromObject_TD_4698_input.getInt32(i, 3);
            tbl_Filter_TD_3859_output.setInt32(r, 3, _p_size289_t);
            r++;
        }
    }
    tbl_Filter_TD_3859_output.setNumRow(r);
    std::cout << "tbl_Filter_TD_3859_output #Row: " << tbl_Filter_TD_3859_output.getNumRow() << std::endl;
}



struct SW_Aggregate_TD_1489_key {
    std::string _p_brand287;
    std::string _p_type288;
    int32_t _p_size289;
    bool operator==(const SW_Aggregate_TD_1489_key& other) const { return (_p_brand287 == other._p_brand287) && (_p_type288 == other._p_type288) && (_p_size289 == other._p_size289); }
};
namespace std {
template <>
struct hash<SW_Aggregate_TD_1489_key> {
    std::size_t operator() (const SW_Aggregate_TD_1489_key& k) const {
        using std::size_t;
        using std::hash;
        using std::string;
        return (hash<string>()(k._p_brand287)) + (hash<string>()(k._p_type288)) + (hash<int32_t>()(k._p_size289));
    }
};
}
struct SW_Aggregate_TD_1489_payload {
    int64_t _supplier_cnt1797L_count_0;
};
void SW_Aggregate_TD_1489(Table &tbl_JOIN_INNER_TD_2464_output, Table &tbl_SerializeFromObject_TD_4698_input, Table &tbl_Aggregate_TD_1489_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: true
    // Supported operation: Aggregate
    // Operation: ListBuffer(p_brand#287, p_type#288, p_size#289, count(distinct ps_suppkey#330) AS supplier_cnt#1797L)
    // Input: ListBuffer(ps_suppkey#330, p_brand#287, p_type#288, p_size#289)
    // Output: ListBuffer(p_brand#287, p_type#288, p_size#289, supplier_cnt#1797L)
    std::unordered_map<SW_Aggregate_TD_1489_key, SW_Aggregate_TD_1489_payload> ht1;
    int nrow1 = tbl_JOIN_INNER_TD_2464_output.getNumRow();
    for (int i = 0; i < nrow1; i++) {
        int32_t _ps_suppkey330 = tbl_JOIN_INNER_TD_2464_output.getInt32(i, 0);
        std::array<char, TPCH_READ_REGION_LEN + 1> _p_brand287 = tbl_SerializeFromObject_TD_4698_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(tbl_JOIN_INNER_TD_2464_output.getInt32(i, 1), 1);
        std::array<char, TPCH_READ_REGION_LEN + 1> _p_type288 = tbl_SerializeFromObject_TD_4698_input.getcharN<char, TPCH_READ_REGION_LEN + 1>(tbl_JOIN_INNER_TD_2464_output.getInt32(i, 2), 2);
        int32_t _p_size289 = tbl_JOIN_INNER_TD_2464_output.getInt32(i, 3);
        SW_Aggregate_TD_1489_key k{std::string(_p_brand287.data()), std::string(_p_type288.data()), _p_size289};
        int64_t _supplier_cnt1797L_count_0 = _ps_suppkey330 != 0 ? 1 : 0;
        SW_Aggregate_TD_1489_payload p{_supplier_cnt1797L_count_0};
        auto it = ht1.find(k);
        if (it != ht1.end()) {
            int64_t count_0 = (it->second)._supplier_cnt1797L_count_0 + _supplier_cnt1797L_count_0;
            p._supplier_cnt1797L_count_0 = count_0;
            ht1[k] = p;
        } else { 
            ht1.insert(std::make_pair(k, p));
        }
    }
    int r = 0;
    for (auto& it : ht1) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _p_brand287{};
        memcpy(_p_brand287.data(), ((it.first)._p_brand287).data(), ((it.first)._p_brand287).length());
        tbl_Aggregate_TD_1489_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(r, 0, _p_brand287);
        std::array<char, TPCH_READ_REGION_LEN + 1> _p_type288{};
        memcpy(_p_type288.data(), ((it.first)._p_type288).data(), ((it.first)._p_type288).length());
        tbl_Aggregate_TD_1489_output.setcharN<char, TPCH_READ_REGION_LEN + 1>(r, 1, _p_type288);
        tbl_Aggregate_TD_1489_output.setInt32(r, 2, (it.first)._p_size289);
        int64_t _supplier_cnt1797L = (it.second)._supplier_cnt1797L_count_0;
        tbl_Aggregate_TD_1489_output.setInt64(r, 3, _supplier_cnt1797L);
        ++r;
    }
    tbl_Aggregate_TD_1489_output.setNumRow(r);
    std::cout << "tbl_Aggregate_TD_1489_output #Row: " << tbl_Aggregate_TD_1489_output.getNumRow() << std::endl;
}

void SW_Sort_TD_0774(Table &tbl_Aggregate_TD_1489_output, Table &tbl_Sort_TD_0774_output) {
    // StringRowIDSubstitution: false StringRowIDBackSubstitution: false
    // Supported operation: Sort
    // Operation: ListBuffer(supplier_cnt#1797L DESC NULLS LAST, p_brand#287 ASC NULLS FIRST, p_type#288 ASC NULLS FIRST, p_size#289 ASC NULLS FIRST)
    // Input: ListBuffer(p_brand#287, p_type#288, p_size#289, supplier_cnt#1797L)
    // Output: ListBuffer(p_brand#287, p_type#288, p_size#289, supplier_cnt#1797L)
    struct SW_Sort_TD_0774Row {
        std::string _p_brand287;
        std::string _p_type288;
        int32_t _p_size289;
        int64_t _supplier_cnt1797L;
    }; 

    struct {
        bool operator()(const SW_Sort_TD_0774Row& a, const SW_Sort_TD_0774Row& b) const { return 
 (a._supplier_cnt1797L > b._supplier_cnt1797L) || 
 ((a._supplier_cnt1797L == b._supplier_cnt1797L) && (a._p_brand287 < b._p_brand287)) || 
 ((a._supplier_cnt1797L == b._supplier_cnt1797L) && (a._p_brand287 == b._p_brand287) && (a._p_type288 < b._p_type288)) || 
 ((a._supplier_cnt1797L == b._supplier_cnt1797L) && (a._p_brand287 == b._p_brand287) && (a._p_type288 == b._p_type288) && (a._p_size289 < b._p_size289)); 
}
    }SW_Sort_TD_0774_order; 

    int nrow1 = tbl_Aggregate_TD_1489_output.getNumRow();
    std::vector<SW_Sort_TD_0774Row> rows;
    for (int i = 0; i < nrow1; i++) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _p_brand287 = tbl_Aggregate_TD_1489_output.getcharN<char, TPCH_READ_REGION_LEN +1>(i, 0);
        std::array<char, TPCH_READ_REGION_LEN + 1> _p_type288 = tbl_Aggregate_TD_1489_output.getcharN<char, TPCH_READ_REGION_LEN +1>(i, 1);
        int32_t _p_size289 = tbl_Aggregate_TD_1489_output.getInt32(i, 2);
        int64_t _supplier_cnt1797L = tbl_Aggregate_TD_1489_output.getInt64(i, 3);
        SW_Sort_TD_0774Row t = {std::string(_p_brand287.data()),std::string(_p_type288.data()),_p_size289,_supplier_cnt1797L};
        rows.push_back(t);
    }
    std::sort(rows.begin(), rows.end(), SW_Sort_TD_0774_order);
    int r = 0;
    for (auto& it : rows) {
        std::array<char, TPCH_READ_REGION_LEN + 1> _p_brand287{};
        memcpy(_p_brand287.data(), (it._p_brand287).data(), (it._p_brand287).length());
        tbl_Sort_TD_0774_output.setcharN<char, TPCH_READ_REGION_LEN +1>(r, 0, _p_brand287);
        std::array<char, TPCH_READ_REGION_LEN + 1> _p_type288{};
        memcpy(_p_type288.data(), (it._p_type288).data(), (it._p_type288).length());
        tbl_Sort_TD_0774_output.setcharN<char, TPCH_READ_REGION_LEN +1>(r, 1, _p_type288);
        tbl_Sort_TD_0774_output.setInt32(r, 2, it._p_size289);
        tbl_Sort_TD_0774_output.setInt64(r, 3, it._supplier_cnt1797L);
        if (r < 10) {
            std::cout << (it._p_brand287).data() << " " << (it._p_type288).data() << " " << it._p_size289 << " " << it._supplier_cnt1797L << " " << std::endl;
        }
        ++r;
    }
    tbl_Sort_TD_0774_output.setNumRow(r);
    std::cout << "tbl_Sort_TD_0774_output #Row: " << tbl_Sort_TD_0774_output.getNumRow() << std::endl;
}

