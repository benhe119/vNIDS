#ifndef CLICKNET_DNS_H
#define CLICKNET_DNS_H
#if CLICK_LINUXMODULE
#include <linux/in.h>
#include <net/checksum.h>
#else
#include <netinet/in.h>
#include <sys/types.h>
#endif
#include <click/string.hh>
#include <set>
#include <vector>
#include "binpac_lib/binpac.h"

#define BINPAC_DNS_PARSER
/** @brief
 * rfc 1035 Header section format
 */
struct click_dns {
  uint16_t dh_id;     /* 0-1 */
  uint8_t dh_flags_1; /* 2 */
#define DH_OPCODE 0x78
  uint8_t dh_flags_2; /* 3 */
#define DH_RCODE 0xf
  uint16_t dh_qdcount; /* 4 question count */
  uint16_t dh_ancount; /* 5 answer count */
  uint16_t dh_nscount; /* 6 authority records count */
  uint16_t dh_arcount; /* 7 additional records count */
};

struct click_dns_info {
  uint16_t dh_ancount; /* answer count */
  uint16_t dns_type;   /* answer type */
#define DNS_TYPE_A 0x1
  uint16_t dns_class; /* answer class */
#define DNS_CLASS_IN 0x1
  uint32_t dns_record_ip; /* answer ip */
  char *qname;            /* query name */
  click_dns_info() : qname(NULL) {}
  ~click_dns_info() {
    if (qname) delete[] qname;
  }
};

#ifndef BINPAC_DNS_PARSER
int dns_parse_info(const unsigned char *, const unsigned char *,
                   const click_dns *, click_dns_info *);
#endif

#ifdef BINPAC_DNS_PARSER
/* @begin */
/*********Add code which generated by Binpac**********/
namespace binpac {
namespace DNS {
class ContextDNS;
class DNS_Conn;
enum DNS_answer_type {
  DNS_QUESTION,
  DNS_ANSWER,
  DNS_AUTHORITY,
  DNS_ADDITIONAL,
};
enum DNS_rdata_type {
  TYPE_A = 1,
  TYPE_NS = 2,
  TYPE_MD = 3,
  TYPE_MF = 4,
  TYPE_CNAME = 5,
  TYPE_SOA = 6,
  TYPE_MB = 7,
  TYPE_MG = 8,
  TYPE_MR = 9,
  TYPE_NULL = 10,
  TYPE_WKS = 11,
  TYPE_PTR = 12,
  TYPE_HINFO = 13,
  TYPE_MINFO = 14,
  TYPE_MX = 15,
  TYPE_TXT = 16,
  TYPE_AAAA = 28,
  TYPE_NBS = 32,
  TYPE_A6 = 38,
  TYPE_EDNS = 41,
};
class DNS_PDU;
class DNS_message;
class DNS_header;
class DNS_question;
class DNS_name;
class DNS_label;
class DNS_rr;
class DNS_rdata;
class DNS_char_string;
class DNS_rdata_MX;
class DNS_rdata_SOA;
class DNS_rdata_WKS;
class DNS_rdata_HINFO;
class DNS_Flow;
}  // namespace DNS

int bytestring_to_int(const_bytestring const &s, int base);
double bytestring_to_double(const_bytestring const &s);
int bytestring_casecmp(const_bytestring const &s1, const_charptr const &s2);
bool bytestring_caseprefix(const_bytestring const &s1, const_charptr const &s2);
namespace DNS {

class ContextDNS {
 public:
  ContextDNS(DNS_Conn *connection, DNS_Flow *flow);
  ~ContextDNS();

  // Member access functions
  DNS_Conn *connection() const { return connection_; }
  DNS_Flow *flow() const { return flow_; }

 protected:
  DNS_Conn *connection_;
  DNS_Flow *flow_;
};

class DNS_Conn : public binpac::ConnectionAnalyzer {
 public:
  DNS_Conn(click_dns_info *info);
  ~DNS_Conn();

  // Member access functions
  DNS_Flow *upflow() const { return upflow_; }
  DNS_Flow *downflow() const { return downflow_; }
  click_dns_info *info() const { return info_; }

  void NewData(bool is_orig, const_byteptr begin, const_byteptr end);
  void NewGap(bool is_orig, int gap_length);
  void FlowEOF(bool is_orig);

 protected:
  DNS_Flow *upflow_;
  DNS_Flow *downflow_;
  click_dns_info *info_;
};

class DNS_PDU {
 public:
  DNS_PDU(bool is_orig);
  ~DNS_PDU();
  int Parse(const_byteptr const t_begin_of_data,
            const_byteptr const t_end_of_data, ContextDNS *t_context);

  // Member access functions
  int val_case_index() const { return val_case_index_; }
  DNS_message *request() const {
    switch (val_case_index()) {
      case 1:
        break;  // OK
      default:
        throw binpac::ExceptionInvalidCase("./dns-protocol.pac:32:request",
                                           val_case_index(), "true");
        break;
    }
    return request_;
  }
  DNS_message *response() const {
    switch (val_case_index()) {
      case 0:
        break;  // OK
      default:
        throw binpac::ExceptionInvalidCase("./dns-protocol.pac:33:response",
                                           val_case_index(), "false");
        break;
    }
    return response_;
  }
  bool is_orig() const { return is_orig_; }

 protected:
  int val_case_index_;
  DNS_message *request_;
  DNS_message *response_;
  bool is_orig_;
};

class DNS_message {
 public:
  DNS_message();
  ~DNS_message();
  int Parse(const_byteptr const t_begin_of_data,
            const_byteptr const t_end_of_data, ContextDNS *t_context);

  // Member access functions
  DNS_header *header() const { return header_; }
  vector<DNS_question *> *question() const { return question_; }
  vector<DNS_rr *> *answer() const { return answer_; }
  vector<DNS_rr *> *authority() const { return authority_; }
  vector<DNS_rr *> *additional() const { return additional_; }
  int byteorder() const { return byteorder_; }
  const_bytestring const &sourcedata() const { return sourcedata_; }

 protected:
  DNS_header *header_;
  vector<DNS_question *> *question_;
  DNS_question *question__elem_;
  vector<DNS_rr *> *answer_;
  DNS_rr *answer__elem_;
  vector<DNS_rr *> *authority_;
  DNS_rr *authority__elem_;
  vector<DNS_rr *> *additional_;
  DNS_rr *additional__elem_;
  int byteorder_;
  const_bytestring sourcedata_;
};

class DNS_header {
 public:
  DNS_header();
  ~DNS_header();
  int Parse(const_byteptr const t_begin_of_data,
            const_byteptr const t_end_of_data, ContextDNS *t_context,
            int t_byteorder);

  // Member access functions
  uint16 id() const { return id_; }
  uint16 qrop() const { return qrop_; }
  uint16 qdcount() const { return qdcount_; }
  uint16 ancount() const { return ancount_; }
  uint16 nscount() const { return nscount_; }
  uint16 arcount() const { return arcount_; }
  bool qr() const { return qr_; }
  uint8 opcode() const { return opcode_; }
  bool aa() const { return aa_; }
  bool tc() const { return tc_; }
  bool rd() const { return rd_; }
  bool ra() const { return ra_; }
  uint8 z() const { return z_; }
  uint8 rcode() const { return rcode_; }
  int proc_dns_header() const { return proc_dns_header_; }

 protected:
  uint16 id_;
  uint16 qrop_;
  uint16 qdcount_;
  uint16 ancount_;
  uint16 nscount_;
  uint16 arcount_;
  bool qr_;
  uint8 opcode_;
  bool aa_;
  bool tc_;
  bool rd_;
  bool ra_;
  uint8 z_;
  uint8 rcode_;
  int proc_dns_header_;
};

class DNS_question {
 public:
  DNS_question(DNS_message *msg);
  ~DNS_question();
  int Parse(const_byteptr const t_begin_of_data,
            const_byteptr const t_end_of_data, ContextDNS *t_context,
            int t_byteorder);

  // Member access functions
  DNS_name *qname() const { return qname_; }
  uint16 qtype() const { return qtype_; }
  uint16 qclass() const { return qclass_; }
  DNS_message *msg() const { return msg_; }
  int proc_dns_question() const { return proc_dns_question_; }

 protected:
  DNS_name *qname_;
  uint16 qtype_;
  uint16 qclass_;
  DNS_message *msg_;
  int proc_dns_question_;
};

class DNS_name {
 public:
  DNS_name(DNS_message *msg);
  ~DNS_name();
  int Parse(const_byteptr const t_begin_of_data,
            const_byteptr const t_end_of_data, ContextDNS *t_context);

  // Member access functions
  vector<DNS_label *> *labels() const { return labels_; }
  DNS_message *msg() const { return msg_; }

 protected:
  vector<DNS_label *> *labels_;
  DNS_label *labels__elem_;
  DNS_message *msg_;
};

class DNS_label {
 public:
  DNS_label(DNS_message *msg);
  ~DNS_label();
  int Parse(const_byteptr const t_begin_of_data,
            const_byteptr const t_end_of_data, ContextDNS *t_context);

  // Member access functions
  uint8 length() const { return length_; }
  int data_case_index() const { return data_case_index_; }
  bytestring const &label() const {
    switch (data_case_index()) {
      case 0:
        break;  // OK
      default:
        throw binpac::ExceptionInvalidCase("./dns-protocol.pac:115:label",
                                           data_case_index(), "((int) 0)");
        break;
    }
    return label_;
  }
  uint8 ptr_lo() const {
    switch (data_case_index()) {
      case 3:
        break;  // OK
      default:
        throw binpac::ExceptionInvalidCase("./dns-protocol.pac:116:ptr_lo",
                                           data_case_index(), "((int) 3)");
        break;
    }
    return ptr_lo_;
  }
  DNS_message *msg() const { return msg_; }
  uint8 label_type() const { return label_type_; }
  bool last() const { return last_; }
  DNS_name *ptr() const {
    BINPAC_ASSERT(has_ptr());
    return ptr_;
  }
  bool has_ptr() const { return has_ptr_; }
  bool clear_pointer_set() const {
    BINPAC_ASSERT(has_clear_pointer_set());
    return clear_pointer_set_;
  }
  bool has_clear_pointer_set() const { return has_clear_pointer_set_; }

 protected:
  uint8 length_;
  int data_case_index_;
  bytestring label_;
  uint8 ptr_lo_;
  DNS_message *msg_;
  uint8 label_type_;
  bool last_;
  DNS_name *ptr_;
  bool has_ptr_;
  bool clear_pointer_set_;
  bool has_clear_pointer_set_;
};

class DNS_rr {
 public:
  DNS_rr(DNS_message *msg, DNS_answer_type answer_type);
  ~DNS_rr();
  int Parse(const_byteptr const t_begin_of_data,
            const_byteptr const t_end_of_data, ContextDNS *t_context,
            int t_byteorder);

  // Member access functions
  DNS_name *rr_name() const { return rr_name_; }
  uint16 rr_type() const { return rr_type_; }
  uint16 rr_class() const { return rr_class_; }
  uint32 rr_ttl() const { return rr_ttl_; }
  uint16 rr_rdlength() const { return rr_rdlength_; }
  DNS_rdata *rr_rdata() const { return rr_rdata_; }
  DNS_message *msg() const { return msg_; }
  DNS_answer_type answer_type() const { return answer_type_; }
  int proc_dns_rr() const { return proc_dns_rr_; }

 protected:
  DNS_name *rr_name_;
  uint16 rr_type_;
  uint16 rr_class_;
  uint32 rr_ttl_;
  uint16 rr_rdlength_;
  DNS_rdata *rr_rdata_;
  DNS_message *msg_;
  DNS_answer_type answer_type_;
  int proc_dns_rr_;
};

class DNS_rdata {
 public:
  DNS_rdata(DNS_message *msg, uint16 rr_type, uint16 rr_class);
  ~DNS_rdata();
  int Parse(const_byteptr const t_begin_of_data,
            const_byteptr const t_end_of_data, ContextDNS *t_context,
            int t_byteorder);

  // Member access functions
  int val_case_index() const { return val_case_index_; }
  uint32 type_a() const {
    switch (val_case_index()) {
      case 1:
        break;  // OK
      default:
        throw binpac::ExceptionInvalidCase("./dns-protocol.pac:166:type_a",
                                           val_case_index(), "TYPE_A");
        break;
    }
    return type_a_;
  }
  DNS_name *type_ns() const {
    switch (val_case_index()) {
      case 2:
        break;  // OK
      default:
        throw binpac::ExceptionInvalidCase("./dns-protocol.pac:167:type_ns",
                                           val_case_index(), "TYPE_NS");
        break;
    }
    return type_ns_;
  }
  DNS_name *type_cname() const {
    switch (val_case_index()) {
      case 5:
        break;  // OK
      default:
        throw binpac::ExceptionInvalidCase("./dns-protocol.pac:168:type_cname",
                                           val_case_index(), "TYPE_CNAME");
        break;
    }
    return type_cname_;
  }
  DNS_rdata_SOA *type_soa() const {
    switch (val_case_index()) {
      case 6:
        break;  // OK
      default:
        throw binpac::ExceptionInvalidCase("./dns-protocol.pac:169:type_soa",
                                           val_case_index(), "TYPE_SOA");
        break;
    }
    return type_soa_;
  }
  DNS_name *type_ptr() const {
    switch (val_case_index()) {
      case 12:
        break;  // OK
      default:
        throw binpac::ExceptionInvalidCase("./dns-protocol.pac:170:type_ptr",
                                           val_case_index(), "TYPE_PTR");
        break;
    }
    return type_ptr_;
  }
  DNS_rdata_MX *type_mx() const {
    switch (val_case_index()) {
      case 15:
        break;  // OK
      default:
        throw binpac::ExceptionInvalidCase("./dns-protocol.pac:171:type_mx",
                                           val_case_index(), "TYPE_MX");
        break;
    }
    return type_mx_;
  }
  vector<uint32> *type_aaaa() const {
    switch (val_case_index()) {
      case 28:
      case 38:
        break;  // OK
      default:
        throw binpac::ExceptionInvalidCase("./dns-protocol.pac:173:type_aaaa",
                                           val_case_index(),
                                           "TYPE_AAAA, TYPE_A6");
        break;
    }
    return type_aaaa_;
  }
  DNS_rdata_WKS *type_wks() const {
    switch (val_case_index()) {
      case 11:
        break;  // OK
      default:
        throw binpac::ExceptionInvalidCase("./dns-protocol.pac:175:type_wks",
                                           val_case_index(), "TYPE_WKS");
        break;
    }
    return type_wks_;
  }
  DNS_rdata_HINFO *type_hinfo() const {
    switch (val_case_index()) {
      case 13:
        break;  // OK
      default:
        throw binpac::ExceptionInvalidCase("./dns-protocol.pac:176:type_hinfo",
                                           val_case_index(), "TYPE_HINFO");
        break;
    }
    return type_hinfo_;
  }
  bytestring const &type_txt() const {
    switch (val_case_index()) {
      case 16:
        break;  // OK
      default:
        throw binpac::ExceptionInvalidCase("./dns-protocol.pac:177:type_txt",
                                           val_case_index(), "TYPE_TXT");
        break;
    }
    return type_txt_;
  }
  bytestring const &unknown() const { return unknown_; }
  DNS_message *msg() const { return msg_; }
  uint16 rr_type() const { return rr_type_; }
  uint16 rr_class() const { return rr_class_; }

 protected:
  int val_case_index_;
  uint32 type_a_;
  DNS_name *type_ns_;
  DNS_name *type_cname_;
  DNS_rdata_SOA *type_soa_;
  DNS_name *type_ptr_;
  DNS_rdata_MX *type_mx_;
  vector<uint32> *type_aaaa_;
  uint32 type_aaaa__elem_;
  DNS_rdata_WKS *type_wks_;
  DNS_rdata_HINFO *type_hinfo_;
  bytestring type_txt_;
  bytestring unknown_;
  DNS_message *msg_;
  uint16 rr_type_;
  uint16 rr_class_;
};

class DNS_char_string {
 public:
  DNS_char_string();
  ~DNS_char_string();
  int Parse(const_byteptr const t_begin_of_data,
            const_byteptr const t_end_of_data);

  // Member access functions
  uint8 length() const { return length_; }
  bytestring const &data() const { return data_; }

 protected:
  uint8 length_;
  bytestring data_;
};

class DNS_rdata_MX {
 public:
  DNS_rdata_MX(DNS_message *msg);
  ~DNS_rdata_MX();
  int Parse(const_byteptr const t_begin_of_data,
            const_byteptr const t_end_of_data, ContextDNS *t_context,
            int t_byteorder);

  // Member access functions
  uint16 preference() const { return preference_; }
  DNS_name *name() const { return name_; }
  DNS_message *msg() const { return msg_; }

 protected:
  uint16 preference_;
  DNS_name *name_;
  DNS_message *msg_;
};

class DNS_rdata_SOA {
 public:
  DNS_rdata_SOA(DNS_message *msg);
  ~DNS_rdata_SOA();
  int Parse(const_byteptr const t_begin_of_data,
            const_byteptr const t_end_of_data, ContextDNS *t_context,
            int t_byteorder);

  // Member access functions
  DNS_name *mname() const { return mname_; }
  DNS_name *rname() const { return rname_; }
  uint32 serial() const { return serial_; }
  uint32 refresh() const { return refresh_; }
  uint32 retry() const { return retry_; }
  uint32 expire() const { return expire_; }
  uint32 minimum() const { return minimum_; }
  DNS_message *msg() const { return msg_; }

 protected:
  DNS_name *mname_;
  DNS_name *rname_;
  uint32 serial_;
  uint32 refresh_;
  uint32 retry_;
  uint32 expire_;
  uint32 minimum_;
  DNS_message *msg_;
};

class DNS_rdata_WKS {
 public:
  DNS_rdata_WKS();
  ~DNS_rdata_WKS();
  int Parse(const_byteptr const t_begin_of_data,
            const_byteptr const t_end_of_data, int t_byteorder);

  // Member access functions
  uint32 address() const { return address_; }
  uint8 protocol() const { return protocol_; }
  bytestring const &bitmap() const { return bitmap_; }

 protected:
  uint32 address_;
  uint8 protocol_;
  bytestring bitmap_;
};

class DNS_rdata_HINFO {
 public:
  DNS_rdata_HINFO();
  ~DNS_rdata_HINFO();
  int Parse(const_byteptr const t_begin_of_data,
            const_byteptr const t_end_of_data);

  // Member access functions
  DNS_char_string *cpu() const { return cpu_; }
  DNS_char_string *os() const { return os_; }

 protected:
  DNS_char_string *cpu_;
  DNS_char_string *os_;
};

class DNS_Flow : public binpac::FlowAnalyzer {
 public:
  DNS_Flow(DNS_Conn *connection, bool is_orig);
  ~DNS_Flow();

  // Member access functions
  DNS_Conn *connection() const { return connection_; }
  bool is_orig() const { return is_orig_; }

  void NewData(const_byteptr t_begin_of_data, const_byteptr t_end_of_data);
  void NewGap(int gap_length);
  void FlowEOF();

  // Functions
  const_bytestring get_pointer(const_bytestring const &msgdata, int offset);
  bool reset_pointer_set();
  bool process_dns_header(DNS_header *hdr);
  bool process_dns_question(DNS_question *question);
  bool process_dns_rr(DNS_rr *rr);

 protected:
  DNS_PDU *dataunit_;
  ContextDNS *context_;

  // Additional members

  set<int> pointer_set;

  DNS_Conn *connection_;
  bool is_orig_;
};

}  // namespace DNS
}  // namespace binpac

/* @end***********/
#endif
#endif
