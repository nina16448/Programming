#include <iostream>
#include <map>
#include <queue>
#include <utility>
#include <climits>
#include <functional> 
#include <iomanip>
#include <stack>
#include <set>

using namespace std;

typedef unsigned int usint;

#define SET(func_name,type,var_name,_var_name) void func_name(type _var_name) { var_name = _var_name ;} 
#define GET(func_name,type,var_name) type func_name() const { return var_name ;}
#define NodID first
#define ActID second
#define Val second
#define nod1 first.first
#define nod2 first.second



class header;
class payload;
class packet;
class node;
class event;
class link; // new
usint dsts_num;
vector <usint> dsts; //存各個終點的ID

// for simplicity, we use a const int to simulate the delay
// if you want to simulate the more details, you should revise it to be a class
const usint ONE_HOP_DELAY = 10;
const usint BROCAST_ID = UINT_MAX;

// BROCAST_ID means that all neighbors are receivers; UINT_MAX is the maximum value of usint

class header{
public:
    virtual ~header(){}

    SET(setSrcID, usint, srcID, _srcID);
    SET(setDstID, usint, dstID, _dstID);
    SET(setPreID, usint, preID, _preID);
    SET(setNexID, usint, nexID, _nexID);
    GET(getSrcID, usint, srcID);
    GET(getDstID, usint, dstID);
    GET(getPreID, usint, preID);
    GET(getNexID, usint, nexID);

    virtual string type() = 0;

    // factory concept: generate a header
    class header_generator{
        // lock the copy constructor
        header_generator(header_generator &){}
        // store all possible types of header
        static map<string, header_generator *> prototypes;
    protected:
        // allow derived class to use it
        header_generator(){}
        // after you create a new header type, please register the factory of this header type by this function
        void register_header_type(header_generator *h){ prototypes[h->type()] = h; }
        // you have to implement your own generate() to generate your header
        virtual header *generate() = 0;
    public:
        // you have to implement your own type() to return your header type
        virtual string type() = 0;
        // this function is used to generate any type of header derived
        static header *generate(string type){
            if(prototypes.find(type) != prototypes.end()){ // if this type derived exists 
                return prototypes[type]->generate(); // generate it!!
            }
            std::cerr << "no such header type" << std::endl; // otherwise
            return nullptr;
        }
        static void print(){
            cout << "registered header types: " << endl;
            for(map<string, header::header_generator *>::iterator it = prototypes.begin(); it != prototypes.end(); it++)
                cout << it->second->type() << endl;
        }
        virtual ~header_generator(){};
    };

protected:
    header() :srcID(BROCAST_ID), dstID(BROCAST_ID), preID(BROCAST_ID), nexID(BROCAST_ID){} // this constructor cannot be directly called by users

private:
    usint srcID;
    usint dstID;
    usint preID;
    usint nexID;
    header(header &){} // this constructor cannot be directly called by users
};
map<string, header::header_generator *> header::header_generator::prototypes;

class SDN_data_header : public header{
    SDN_data_header(SDN_data_header &){} // cannot be called by users

protected:
    SDN_data_header(){} // this constructor cannot be directly called by users

public:
    ~SDN_data_header(){}
    string type(){ return "SDN_data_header"; }

    class SDN_data_header_generator;
    friend class SDN_data_header_generator;
    // SDN_data_header_generator is derived from header_generator to generate a header
    class SDN_data_header_generator : public header_generator{
        static SDN_data_header_generator sample;
        // this constructor is only for sample to register this header type
        SDN_data_header_generator(){ /*cout << "SDN_data_header registered" << endl;*/ register_header_type(&sample); }
    protected:
        virtual header *generate(){
            // cout << "SDN_data_header generated" << endl;
            return new SDN_data_header;
        }
    public:
        virtual string type(){ return "SDN_data_header"; }
        ~SDN_data_header_generator(){}

    };
};
SDN_data_header::SDN_data_header_generator SDN_data_header::SDN_data_header_generator::sample;

class SDN_ctrl_header : public header{
    SDN_ctrl_header(SDN_ctrl_header &){} // cannot be called by users

protected:
    SDN_ctrl_header(){} // this constructor cannot be directly called by users

public:
    ~SDN_ctrl_header(){}
    string type(){ return "SDN_ctrl_header"; }

    class SDN_ctrl_header_generator;
    friend class SDN_ctrl_header_generator;
    // SDN_ctrl_header_generator is derived from header_generator to generate a header
    class SDN_ctrl_header_generator : public header_generator{
        static SDN_ctrl_header_generator sample;
        // this constructor is only for sample to register this header type
        SDN_ctrl_header_generator(){ /*cout << "SDN_ctrl_header registered" << endl;*/ register_header_type(&sample); }
    protected:
        virtual header *generate(){
            // cout << "SDN_ctrl_header generated" << endl;
            return new SDN_ctrl_header;
        }
    public:
        virtual string type(){ return "SDN_ctrl_header"; }
        ~SDN_ctrl_header_generator(){}

    };
};
SDN_ctrl_header::SDN_ctrl_header_generator SDN_ctrl_header::SDN_ctrl_header_generator::sample;

class SDN_stat_header : public header{
    SDN_stat_header(SDN_stat_header &){} // cannot be called by users

protected:
    SDN_stat_header(){} // this constructor cannot be directly called by users

public:
    ~SDN_stat_header(){}
    string type(){ return "SDN_stat_header"; }

    class SDN_stat_header_generator;
    friend class SDN_stat_header_generator;
    // SDN_stat_header_generator is derived from header_generator to generate a header
    class SDN_stat_header_generator : public header_generator{
        static SDN_stat_header_generator sample;
        // this constructor is only for sample to register this header type
        SDN_stat_header_generator(){ /*cout << "SDN_stat_header registered" << endl;*/ register_header_type(&sample); }
    protected:
        virtual header *generate(){
            // cout << "SDN_stat_header generated" << endl;
            return new SDN_stat_header;
        }
    public:
        virtual string type(){ return "SDN_stat_header"; }
        ~SDN_stat_header_generator(){}

    };
};
SDN_stat_header::SDN_stat_header_generator SDN_stat_header::SDN_stat_header_generator::sample;


class payload{
    payload(payload &){} // this constructor cannot be directly called by users

    string msg;

protected:
    payload(){}
public:
    virtual ~payload(){}
    virtual string type() = 0;

    SET(setMsg, string, msg, _msg);
    GET(getMsg, string, msg);

    class payload_generator{
        // lock the copy constructor
        payload_generator(payload_generator &){}
        // store all possible types of header
        static map<string, payload_generator *> prototypes;
    protected:
        // allow derived class to use it
        payload_generator(){}
        // after you create a new payload type, please register the factory of this payload type by this function
        void register_payload_type(payload_generator *h){ prototypes[h->type()] = h; }
        // you have to implement your own generate() to generate your payload
        virtual payload *generate() = 0;
    public:
        // you have to implement your own type() to return your header type
        virtual string type() = 0;
        // this function is used to generate any type of header derived
        static payload *generate(string type){
            if(prototypes.find(type) != prototypes.end()){ // if this type derived exists 
                return prototypes[type]->generate(); // generate it!!
            }
            std::cerr << "no such payload type" << std::endl; // otherwise
            return nullptr;
        }
        static void print(){
            cout << "registered payload types: " << endl;
            for(map<string, payload::payload_generator *>::iterator it = prototypes.begin(); it != prototypes.end(); it++)
                cout << it->second->type() << endl;
        }
        virtual ~payload_generator(){};
    };
};
map<string, payload::payload_generator *> payload::payload_generator::prototypes;


class SDN_data_payload : public payload{
    SDN_data_payload(SDN_data_payload &){}

protected:
    SDN_data_payload(){} // this constructor cannot be directly called by users
public:
    ~SDN_data_payload(){}

    string type(){ return "SDN_data_payload"; }

    class SDN_data_payload_generator;
    friend class SDN_data_payload_generator;
    // SDN_data_payload is derived from payload_generator to generate a payload
    class SDN_data_payload_generator : public payload_generator{
        static SDN_data_payload_generator sample;
        // this constructor is only for sample to register this payload type
        SDN_data_payload_generator(){ /*cout << "SDN_data_payload registered" << endl;*/ register_payload_type(&sample); }
    protected:
        virtual payload *generate(){
            // cout << "SDN_data_payload generated" << endl;
            return new SDN_data_payload;
        }
    public:
        virtual string type(){ return "SDN_data_payload"; }
        ~SDN_data_payload_generator(){}
    };
};
SDN_data_payload::SDN_data_payload_generator SDN_data_payload::SDN_data_payload_generator::sample;

class SDN_ctrl_payload : public payload{
    SDN_ctrl_payload(SDN_ctrl_payload &){}

    usint matID; // match: target
    usint actID; // action: the next hop

protected:
    SDN_ctrl_payload(){} // this constructor cannot be directly called by users
public:
    ~SDN_ctrl_payload(){}

    string type(){ return "SDN_ctrl_payload"; }

    SET(setMatID, usint, matID, _matID);
    GET(getMatID, usint, matID);
    SET(setActID, usint, actID, _actID);
    GET(getActID, usint, actID);


    class SDN_ctrl_payload_generator;
    friend class SDN_ctrl_payload_generator;
    // SDN_data_payload is derived from payload_generator to generate a payload
    class SDN_ctrl_payload_generator : public payload_generator{
        static SDN_ctrl_payload_generator sample;
        // this constructor is only for sample to register this payload type
        SDN_ctrl_payload_generator(){ /*cout << "SDN_ctrl_payload registered" << endl;*/ register_payload_type(&sample); }
    protected:
        virtual payload *generate(){
            // cout << "SDN_ctrl_payload generated" << endl;
            return new SDN_ctrl_payload;
        }
    public:
        virtual string type(){ return "SDN_ctrl_payload"; }
        ~SDN_ctrl_payload_generator(){}
    };
};
SDN_ctrl_payload::SDN_ctrl_payload_generator SDN_ctrl_payload::SDN_ctrl_payload_generator::sample;

class SDN_stat_payload : public payload{
    SDN_stat_payload(SDN_stat_payload &){}

    usint RootID; // point ID
    map <usint, usint> NeiList; // he's neighbor <neiID, weight>


protected:
    SDN_stat_payload(){} // this constructor cannot be directly called by users
public:
    ~SDN_stat_payload(){}

    string type(){ return "SDN_stat_payload"; }

    SET(setRootID, usint, RootID, _RootID);
    GET(getRootID, usint, RootID);

    void setNeiList(map <usint, usint> _NeiList){ NeiList = _NeiList; }
    map <usint, usint> getNeiList() const{ return NeiList; }


    class SDN_stat_payload_generator;
    friend class SDN_stat_payload_generator;
    // SDN_data_payload is derived from payload_generator to generate a payload
    class SDN_stat_payload_generator : public payload_generator{
        static SDN_stat_payload_generator sample;
        // this constructor is only for sample to register this payload type
        SDN_stat_payload_generator(){ /*cout << "SDN_stat_payload registered" << endl;*/ register_payload_type(&sample); }
    protected:
        virtual payload *generate(){
            // cout << "SDN_stat_payload generated" << endl;
            return new SDN_stat_payload;
        }
    public:
        virtual string type(){ return "SDN_stat_payload"; }
        ~SDN_stat_payload_generator(){}
    };
};
SDN_stat_payload::SDN_stat_payload_generator SDN_stat_payload::SDN_stat_payload_generator::sample;


class packet{
    // a packet usually contains a header and a payload
    header *hdr;
    payload *pld;
    usint p_id;
    static usint last_packet_id;

    packet(packet &){}
    static int live_packet_num;
protected:
    // these constructors cannot be directly called by users
    packet() : hdr(nullptr), pld(nullptr){ p_id = last_packet_id++; live_packet_num++; }
    packet(string _hdr, string _pld, bool rep = false, usint rep_id = 0){
        if(!rep) // a duplicated packet does not have a new packet id
            p_id = last_packet_id++;
        else
            p_id = rep_id;
        hdr = header::header_generator::generate(_hdr);
        pld = payload::payload_generator::generate(_pld);
        live_packet_num++;
    }
public:
    virtual ~packet(){
        // cout << "packet destructor begin" << endl;
        if(hdr != nullptr)
            delete hdr;
        if(pld != nullptr)
            delete pld;
        live_packet_num--;
        // cout << "packet destructor end" << endl;
    }

    SET(setHeader, header *, hdr, _hdr);
    GET(getHeader, header *, hdr);
    SET(setPayload, payload *, pld, _pld);
    GET(getPayload, payload *, pld);
    GET(getPacketID, usint, p_id);

    static void discard(packet *&p){
        // cout << "checking" << endl;
        if(p != nullptr){
            // cout << "discarding" << endl;
            // cout << p->type() << endl;
            delete p;
            // cout << "discarded" << endl;
        }
        p = nullptr;
        // cout << "checked" << endl;
    }
    virtual string type() = 0;

    static int getLivePacketNum(){ return live_packet_num; }

    class packet_generator;
    friend class packet_generator;
    class packet_generator{
        // lock the copy constructor
        packet_generator(packet_generator &){}
        // store all possible types of packet
        static map<string, packet_generator *> prototypes;
    protected:
        // allow derived class to use it
        packet_generator(){}
        // after you create a new packet type, please register the factory of this payload type by this function
        void register_packet_type(packet_generator *h){ prototypes[h->type()] = h; }
        // you have to implement your own generate() to generate your payload
        virtual packet *generate(packet *p = nullptr) = 0;
    public:
        // you have to implement your own type() to return your packet type
        virtual string type() = 0;
        // this function is used to generate any type of packet derived
        static packet *generate(string type){
            if(prototypes.find(type) != prototypes.end()){ // if this type derived exists 
                return prototypes[type]->generate(); // generate it!!
            }
            std::cerr << "no such packet type" << std::endl; // otherwise
            return nullptr;
        }
        static packet *replicate(packet *p){
            if(prototypes.find(p->type()) != prototypes.end()){ // if this type derived exists 
                return prototypes[p->type()]->generate(p); // generate it!!
            }
            std::cerr << "no such packet type" << std::endl; // otherwise
            return nullptr;
        }
        static void print(){
            cout << "registered packet types: " << endl;
            for(map<string, packet::packet_generator *>::iterator it = prototypes.begin(); it != prototypes.end(); it++)
                cout << it->second->type() << endl;
        }
        virtual ~packet_generator(){};
    };
};
map<string, packet::packet_generator *> packet::packet_generator::prototypes;
usint packet::last_packet_id = 0;
int packet::live_packet_num = 0;


// this packet is used to tell the destination the msg
class SDN_data_packet : public packet{
    SDN_data_packet(SDN_data_packet &){}

protected:
    SDN_data_packet(){} // this constructor cannot be directly called by users
    SDN_data_packet(packet *p) : packet(p->getHeader()->type(), p->getPayload()->type(), true, p->getPacketID()){
        *(dynamic_cast<SDN_data_header *>(this->getHeader())) = *(dynamic_cast<SDN_data_header *> (p->getHeader()));
        *(dynamic_cast<SDN_data_payload *>(this->getPayload())) = *(dynamic_cast<SDN_data_payload *> (p->getPayload()));
        //DFS_path = (dynamic_cast<SDN_data_header*>(p))->DFS_path;
        //isVisited = (dynamic_cast<SDN_data_header*>(p))->isVisited;
    } // for duplicate
    SDN_data_packet(string _h, string _p) : packet(_h, _p){}

public:
    virtual ~SDN_data_packet(){}
    string type(){ return "SDN_data_packet"; }

    class SDN_data_packet_generator;
    friend class SDN_data_packet_generator;
    // SDN_data_packet is derived from packet_generator to generate a pub packet
    class SDN_data_packet_generator : public packet_generator{
        static SDN_data_packet_generator sample;
        // this constructor is only for sample to register this packet type
        SDN_data_packet_generator(){ /*cout << "SDN_data_packet registered" << endl;*/ register_packet_type(&sample); }
    protected:
        virtual packet *generate(packet *p = nullptr){
            // cout << "SDN_data_packet generated" << endl;
            if(nullptr == p)
                return new SDN_data_packet("SDN_data_header", "SDN_data_payload");
            else
                return new SDN_data_packet(p); // duplicate
        }
    public:
        virtual string type(){ return "SDN_data_packet"; }
        ~SDN_data_packet_generator(){}
    };
};
SDN_data_packet::SDN_data_packet_generator SDN_data_packet::SDN_data_packet_generator::sample;

class SDN_ctrl_packet : public packet{
    SDN_ctrl_packet(SDN_ctrl_packet &){}

protected:
    SDN_ctrl_packet(){} // this constructor cannot be directly called by users
    SDN_ctrl_packet(packet *p) : packet(p->getHeader()->type(), p->getPayload()->type(), true, p->getPacketID()){
        *(dynamic_cast<SDN_ctrl_header *>(this->getHeader())) = *(dynamic_cast<SDN_ctrl_header *> (p->getHeader()));
        *(dynamic_cast<SDN_ctrl_payload *>(this->getPayload())) = *(dynamic_cast<SDN_ctrl_payload *> (p->getPayload()));
        //DFS_path = (dynamic_cast<SDN_ctrl_header*>(p))->DFS_path;
        //isVisited = (dynamic_cast<SDN_ctrl_header*>(p))->isVisited;
    } // for duplicate
    SDN_ctrl_packet(string _h, string _p) : packet(_h, _p){}

public:
    virtual ~SDN_ctrl_packet(){}
    string type(){ return "SDN_ctrl_packet"; }

    class SDN_ctrl_packet_generator;
    friend class SDN_ctrl_packet_generator;
    // SDN_ctrl_packet is derived from packet_generator to generate a pub packet
    class SDN_ctrl_packet_generator : public packet_generator{
        static SDN_ctrl_packet_generator sample;
        // this constructor is only for sample to register this packet type
        SDN_ctrl_packet_generator(){ /*cout << "SDN_ctrl_packet registered" << endl;*/ register_packet_type(&sample); }
    protected:
        virtual packet *generate(packet *p = nullptr){
            // cout << "SDN_ctrl_packet generated" << endl;
            if(nullptr == p)
                return new SDN_ctrl_packet("SDN_ctrl_header", "SDN_ctrl_payload");
            else
                return new SDN_ctrl_packet(p); // duplicate
        }
    public:
        virtual string type(){ return "SDN_ctrl_packet"; }
        ~SDN_ctrl_packet_generator(){}
    };
};
SDN_ctrl_packet::SDN_ctrl_packet_generator SDN_ctrl_packet::SDN_ctrl_packet_generator::sample;

class SDN_stat_packet : public packet{
    SDN_stat_packet(SDN_stat_packet &){}

protected:
    SDN_stat_packet(){} // this constructor cannot be directly called by users
    SDN_stat_packet(packet *p) : packet(p->getHeader()->type(), p->getPayload()->type(), true, p->getPacketID()){
        *(dynamic_cast<SDN_stat_header *>(this->getHeader())) = *(dynamic_cast<SDN_stat_header *> (p->getHeader()));
        *(dynamic_cast<SDN_stat_payload *>(this->getPayload())) = *(dynamic_cast<SDN_stat_payload *> (p->getPayload()));
        //DFS_path = (dynamic_cast<SDN_stat_header*>(p))->DFS_path;
        //isVisited = (dynamic_cast<SDN_stat_header*>(p))->isVisited;
    } // for duplicate
    SDN_stat_packet(string _h, string _p) : packet(_h, _p){}

public:
    virtual ~SDN_stat_packet(){}
    string type(){ return "SDN_stat_packet"; }

    class SDN_stat_packet_generator;
    friend class SDN_stat_packet_generator;
    // SDN_stat_packet is derived from packet_generator to generate a pub packet
    class SDN_stat_packet_generator : public packet_generator{
        static SDN_stat_packet_generator sample;
        // this constructor is only for sample to register this packet type
        SDN_stat_packet_generator(){ /*cout << "SDN_stat_packet registered" << endl;*/ register_packet_type(&sample); }
    protected:
        virtual packet *generate(packet *p = nullptr){
            // cout << "SDN_stat_packet generated" << endl;
            if(nullptr == p)
                return new SDN_stat_packet("SDN_stat_header", "SDN_stat_payload");
            else
                return new SDN_stat_packet(p); // duplicate
        }
    public:
        virtual string type(){ return "SDN_stat_packet"; }
        ~SDN_stat_packet_generator(){}
    };
};
SDN_stat_packet::SDN_stat_packet_generator SDN_stat_packet::SDN_stat_packet_generator::sample;


class node{
    // all nodes created in the program
    static map<usint, node *> id_node_table;

    usint id;
    map<usint, bool> phy_neighbors;

protected:
    node(node &){} // this constructor should not be used
    node(){} // this constructor should not be used
    node(usint _id) : id(_id){ id_node_table[_id] = this; }
public:
    virtual ~node(){ // erase the node
        id_node_table.erase(id);
    }
    virtual string type() = 0; // please define it in your derived node class

    void add_phy_neighbor(usint _id, string link_type = "simple_link"); // we only add a directed link from id to _id
    void del_phy_neighbor(usint _id); // we only delete a directed link from id to _id

    // you can use the function to get the node's neigbhors at this time
    // but in the project 3, you are not allowed to use this function 
    const map<usint, bool> &getPhyNeighbors(){
        return phy_neighbors;
    }


    void recv(packet *p){
        packet *tp = p;
        recv_handler(tp);
        packet::discard(p);
    } // the packet will be directly deleted after the handler
    void send(packet *p);

    // receive the packet and do something; this is a pure virtual function
    virtual void recv_handler(packet *p) = 0;
    void send_handler(packet *P);

    static node *id_to_node(usint _id){ return ((id_node_table.find(_id) != id_node_table.end()) ? id_node_table[_id] : nullptr); }
    GET(getNodeID, usint, id);

    static void del_node(usint _id){
        if(id_node_table.find(_id) != id_node_table.end())
            id_node_table.erase(_id);
    }
    static usint getNodeNum(){ return id_node_table.size(); }

    class node_generator{
        // lock the copy constructor
        node_generator(node_generator &){}
        // store all possible types of node
        static map<string, node_generator *> prototypes;
    protected:
        // allow derived class to use it
        node_generator(){}
        // after you create a new node type, please register the factory of this node type by this function
        void register_node_type(node_generator *h){ prototypes[h->type()] = h; }
        // you have to implement your own generate() to generate your node
        virtual node *generate(usint _id) = 0;
    public:
        // you have to implement your own type() to return your node type
        virtual string type() = 0;
        // this function is used to generate any type of node derived
        static node *generate(string type, usint _id){
            if(id_node_table.find(_id) != id_node_table.end()){
                std::cerr << "duplicate node id" << std::endl; // node id is duplicated
                return nullptr;
            }
            else if(BROCAST_ID == _id){
                cerr << "BROCAST_ID cannot be used" << endl;
                return nullptr;
            }
            else if(prototypes.find(type) != prototypes.end()){ // if this type derived exists 
                node *created_node = prototypes[type]->generate(_id);
                return created_node; // generate it!!
            }
            std::cerr << "no such node type" << std::endl; // otherwise
            return nullptr;
        }
        static void print(){
            cout << "registered node types: " << endl;
            for(map<string, node::node_generator *>::iterator it = prototypes.begin(); it != prototypes.end(); it++)
                cout << it->second->type() << endl;
        }
        virtual ~node_generator(){};
    };
};
map<string, node::node_generator *> node::node_generator::prototypes;
map<usint, node *> node::id_node_table;

class SDN_switch : public node{
    // map<usint,bool> one_hop_neighbors; // you can use this variable to record the node's 1-hop neighbors 
    // bool hi; // this is used for example; you can remove it when doing hw2
    map <usint, usint> table; // <destination ID, next node ID>

protected:
    SDN_switch(){} // it should not be used
    SDN_switch(SDN_switch &){} // it should not be used
    SDN_switch(usint _id) : node(_id){} // this constructor cannot be directly called by users

public:
    ~SDN_switch(){}
    string type(){ return "SDN_switch"; }

    // please define recv_handler function to deal with the incoming packet
    virtual void recv_handler(packet *p);

    // void add_one_hop_neighbor (usint n_id) { one_hop_neighbors[n_id] = true; }
    // usint get_one_hop_neighbor_num () { return one_hop_neighbors.size(); }

    class SDN_switch_generator;
    friend class SDN_switch_generator;
    // SDN_switch is derived from node_generator to generate a node
    class SDN_switch_generator : public node_generator{
        static SDN_switch_generator sample;
        // this constructor is only for sample to register this node type
        SDN_switch_generator(){ /*cout << "SDN_switch registered" << endl;*/ register_node_type(&sample); }
    protected:
        virtual node *generate(usint _id){ /*cout << "SDN_switch generated" << endl;*/ return new SDN_switch(_id); }
    public:
        virtual string type(){ return "SDN_switch"; }
        ~SDN_switch_generator(){}
    };
};
SDN_switch::SDN_switch_generator SDN_switch::SDN_switch_generator::sample;

class SDN_controller : public node{
    map <pair <usint, usint>, usint> update_table;  // map <nodeID, DstID, update_state>
    map <usint, usint> upd_round;
    usint dataflag; //紀錄stat pkt有沒有建完所有點
    map <pair <usint, usint>, usint> data_graph; //要做SPT的圖 <node1, node2, weight>
    map <pair <usint, usint>, usint> road; // <node1, dst>, next
    vector <usint> shortest; //node到dst的最短距離
    map <pair <usint, usint>, vector <pair <usint, usint> > > Upd_Round; // map < {dstID, round}, {Nod_ID, Act_ID} >
    vector <usint> round;
    usint SPTflag;
    void Traverse(usint parent, usint Dst_ID);
    map <pair <usint, usint>, set <usint> > SPT; // {node_ID, Dst_ID}對應到在終點為DstID時有哪些點的Next為這個node
    void Bellman_Ford(usint dstID);

protected:
    SDN_controller(){} // it should not be used
    SDN_controller(SDN_controller &){} // it should not be used
    SDN_controller(usint _id) : node(_id), dataflag(0){} // this constructor cannot be directly called by users

public:
    ~SDN_controller(){}
    string type(){ return "SDN_controller"; }

    // please define recv_handler function to deal with the incoming packet
    virtual void recv_handler(packet *p);

    // void add_one_hop_neighbor (usint n_id) { one_hop_neighbors[n_id] = true; }
    // usint get_one_hop_neighbor_num () { return one_hop_neighbors.size(); }

    class SDN_controller_generator;
    friend class SDN_controller_generator;
    // SDN_switch is derived from node_generator to generate a node
    class SDN_controller_generator : public node_generator{
        static SDN_controller_generator sample;
        // this constructor is only for sample to register this node type
        SDN_controller_generator(){ /*cout << "SDN_switch registered" << endl;*/ register_node_type(&sample); }
    protected:
        virtual node *generate(usint _id){ /*cout << "SDN_switch generated" << endl;*/ return new SDN_controller(_id); }
    public:
        virtual string type(){ return "SDN_controller"; }
        ~SDN_controller_generator(){}
    };
};
SDN_controller::SDN_controller_generator SDN_controller::SDN_controller_generator::sample;

class mycomp{
    bool reverse;

public:
    mycomp(const bool &revparam = false){ reverse = revparam; }
    bool operator() (const event *lhs, const event *rhs) const;
};

class event{
    event(event *&){} // this constructor cannot be directly called by users
    static priority_queue < event *, vector < event * >, mycomp > events;
    static usint cur_time; // timer
    static usint end_time;

    // get the next event
    static event *get_next_event();
    static void add_event(event *e){ events.push(e); }
    static hash<string> event_seq;

protected:
    usint trigger_time;

    event(){} // it should not be used
    event(usint _trigger_time) : trigger_time(_trigger_time){}

public:
    virtual void trigger() = 0;
    virtual ~event(){}

    virtual usint event_priority() const = 0;
    usint get_hash_value(string string_for_hash) const{
        usint priority = event_seq(string_for_hash);
        return priority;
    }

    static void flush_events(); // only for debug

    GET(getTriggerTime, usint, trigger_time);

    static void start_simulate(usint _end_time); // the function is used to start the simulation

    static usint getCurTime(){ return cur_time; }
    static void getCurTime(usint _cur_time){ cur_time = _cur_time; }
    // static usint getEndTime() { return end_time ; }
    // static void getEndTime(usint _end_time) { end_time = _end_time; }

    virtual void print() const = 0; // the function is used to print the event information

    class event_generator{
        // lock the copy constructor
        event_generator(event_generator &){}
        // store all possible types of event
        static map<string, event_generator *> prototypes;
    protected:
        // allow derived class to use it
        event_generator(){}
        // after you create a new event type, please register the factory of this event type by this function
        void register_event_type(event_generator *h){ prototypes[h->type()] = h; }
        // you have to implement your own generate() to generate your event
        virtual event *generate(usint _trigger_time, void *data) = 0;
    public:
        // you have to implement your own type() to return your event type
        virtual string type() = 0;
        // this function is used to generate any type of event derived
        static event *generate(string type, usint _trigger_time, void *data){
            if(prototypes.find(type) != prototypes.end()){ // if this type derived exists
                event *e = prototypes[type]->generate(_trigger_time, data);
                add_event(e);
                return e; // generate it!!
            }
            std::cerr << "no such event type" << std::endl; // otherwise
            return nullptr;
        }
        static void print(){
            cout << "registered event types: " << endl;
            for(map<string, event::event_generator *>::iterator it = prototypes.begin(); it != prototypes.end(); it++)
                cout << it->second->type() << endl;
        }
        virtual ~event_generator(){}
    };
};
map<string, event::event_generator *> event::event_generator::prototypes;
priority_queue < event *, vector< event * >, mycomp > event::events;
hash<string> event::event_seq;

usint event::cur_time = 0;
usint event::end_time = 0;

void event::flush_events(){
    cout << "**flush begin" << endl;
    while(!events.empty()){
        cout << setw(11) << events.top()->trigger_time << ": " << setw(11) << events.top()->event_priority() << endl;
        delete events.top();
        events.pop();
    }
    cout << "**flush end" << endl;
}
event *event::get_next_event(){
    if(events.empty())
        return nullptr;
    event *e = events.top();
    events.pop();
    // cout << events.size() << " events remains" << endl;
    return e;
}
void event::start_simulate(usint _end_time){
    if(_end_time < 0){
        cerr << "you should give a possitive value of _end_time" << endl;
        return;
    }
    end_time = _end_time;
    event *e;
    e = event::get_next_event();
    while(e != nullptr && e->trigger_time <= end_time){
        if(cur_time <= e->trigger_time)
            cur_time = e->trigger_time;
        else{
            cerr << "cur_time = " << cur_time << ", event trigger_time = " << e->trigger_time << endl;
            break;
        }

        // cout << "event trigger_time = " << e->trigger_time << endl;
        e->print(); // for log
        // cout << " event begin" << endl;
        e->trigger();
        // cout << " event end" << endl;
        delete e;
        e = event::get_next_event();
    }
    // cout << "no more event" << endl;
}

bool mycomp::operator() (const event *lhs, const event *rhs) const{
    // cout << lhs->getTriggerTime() << ", " << rhs->getTriggerTime() << endl;
    // cout << lhs->type() << ", " << rhs->type() << endl;
    usint lhs_pri = lhs->event_priority();
    usint rhs_pri = rhs->event_priority();
    // cout << "lhs hash = " << lhs_pri << endl;
    // cout << "rhs hash = " << rhs_pri << endl;

    if(reverse)
        return ((lhs->getTriggerTime()) == (rhs->getTriggerTime())) ? (lhs_pri < rhs_pri) : ((lhs->getTriggerTime()) < (rhs->getTriggerTime()));
    else
        return ((lhs->getTriggerTime()) == (rhs->getTriggerTime())) ? (lhs_pri > rhs_pri) : ((lhs->getTriggerTime()) > (rhs->getTriggerTime()));
}

class recv_event : public event{
public:
    class recv_data; // forward declaration

private:
    recv_event(recv_event &){} // this constructor cannot be used
    recv_event(){} // we don't allow users to new a recv_event by themselv
    usint senderID; // the sender
    usint receiverID; // the receiver; the packet will be given to the receiver
    packet *pkt; // the packet

protected:
    // this constructor cannot be directly called by users; only by generator
    recv_event(usint _trigger_time, void *data) : event(_trigger_time), senderID(BROCAST_ID), receiverID(BROCAST_ID), pkt(nullptr){
        recv_data *data_ptr = (recv_data *)data;
        senderID = data_ptr->s_id;
        receiverID = data_ptr->r_id; // the packet will be given to the receiver
        pkt = data_ptr->_pkt;
    }

public:
    virtual ~recv_event(){}
    // recv_event will trigger the recv function
    virtual void trigger();

    usint event_priority() const;

    class recv_event_generator;
    friend class recv_event_generator;
    // recv_event is derived from event_generator to generate a event
    class recv_event_generator : public event_generator{
        static recv_event_generator sample;
        // this constructor is only for sample to register this event type
        recv_event_generator(){ /*cout << "recv_event registered" << endl;*/ register_event_type(&sample); }
    protected:
        virtual event *generate(usint _trigger_time, void *data){
            // cout << "recv_event generated" << endl; 
            return new recv_event(_trigger_time, data);
        }

    public:
        virtual string type(){ return "recv_event"; }
        ~recv_event_generator(){}
    };
    // this class is used to initialize the recv_event
    class recv_data{
    public:
        usint s_id;
        usint r_id;
        packet *_pkt;
    };

    void print() const;
};
recv_event::recv_event_generator recv_event::recv_event_generator::sample;

void recv_event::trigger(){
    if(pkt == nullptr){
        cerr << "recv_event error: no pkt!" << endl;
        return;
    }
    else if(node::id_to_node(receiverID) == nullptr){
        cerr << "recv_event error: no node " << receiverID << "!" << endl;
        delete pkt; return;
    }
    node::id_to_node(receiverID)->recv(pkt);
}
usint recv_event::event_priority() const{
    string string_for_hash;
    string_for_hash = to_string(getTriggerTime()) + to_string(senderID) + to_string(receiverID) + to_string(pkt->getPacketID());
    return get_hash_value(string_for_hash);
}
// the recv_event::print() function is used for log file
void recv_event::print() const{
    cout << "time " << setw(11) << event::getCurTime()
        << "   recID" << setw(11) << receiverID
        << "   pktID" << setw(11) << pkt->getPacketID()
        << "   srcID" << setw(11) << pkt->getHeader()->getSrcID()
        << "   dstID" << setw(11) << pkt->getHeader()->getDstID()
        << "   preID" << setw(11) << pkt->getHeader()->getPreID()
        << "   nexID" << setw(11) << pkt->getHeader()->getNexID()
        << "   " << pkt->type()
        << endl;
    // cout << pkt->type()
    //      << "   time "       << setw(11) << event::getCurTime() 
    //      << "   recID "      << setw(11) << receiverID 
    //      << "   pktID"       << setw(11) << pkt->getPacketID()
    //      << "   srcID "      << setw(11) << pkt->getHeader()->getSrcID() 
    //      << "   dstID"       << setw(11) << pkt->getHeader()->getDstID() 
    //      << "   preID"       << setw(11) << pkt->getHeader()->getPreID()
    //      << "   nexID"       << setw(11) << pkt->getHeader()->getNexID()
    //      << endl;
}

class send_event : public event{
public:
    class send_data; // forward declaration

private:
    send_event(send_event &){}
    send_event(){} // we don't allow users to new a recv_event by themselves
    // this constructor cannot be directly called by users; only by generator
    usint senderID; // the sender
    usint receiverID; // the receiver 
    packet *pkt; // the packet

protected:
    send_event(usint _trigger_time, void *data) : event(_trigger_time), senderID(BROCAST_ID), receiverID(BROCAST_ID), pkt(nullptr){
        send_data *data_ptr = (send_data *)data;
        senderID = data_ptr->s_id;
        receiverID = data_ptr->r_id;
        pkt = data_ptr->_pkt;
    }

public:
    virtual ~send_event(){}
    // send_event will trigger the send function
    virtual void trigger();

    usint event_priority() const;

    class send_event_generator;
    friend class send_event_generator;
    // send_event is derived from event_generator to generate a event
    class send_event_generator : public event_generator{
        static send_event_generator sample;
        // this constructor is only for sample to register this event type
        send_event_generator(){ /*cout << "send_event registered" << endl;*/ register_event_type(&sample); }
    protected:
        virtual event *generate(usint _trigger_time, void *data){
            // cout << "send_event generated" << endl; 
            return new send_event(_trigger_time, data);
        }

    public:
        virtual string type(){ return "send_event"; }
        ~send_event_generator(){}
    };
    // this class is used to initialize the send_event
    class send_data{
    public:
        usint s_id;
        usint r_id;
        packet *_pkt;
        usint t;
    };

    void print() const;
};
send_event::send_event_generator send_event::send_event_generator::sample;

void send_event::trigger(){
    if(pkt == nullptr){
        cerr << "send_event error: no pkt!" << endl;
        return;
    }
    else if(node::id_to_node(senderID) == nullptr){
        cerr << "send_event error: no node " << senderID << "!" << endl;
        delete pkt; return;
    }
    node::id_to_node(senderID)->send(pkt);
}
usint send_event::event_priority() const{
    string string_for_hash;
    string_for_hash = to_string(getTriggerTime()) + to_string(senderID) + to_string(receiverID) + to_string(pkt->getPacketID());
    return get_hash_value(string_for_hash);
}
// the send_event::print() function is used for log file
void send_event::print() const{
    cout << "time " << setw(11) << event::getCurTime()
        << "   senID" << setw(11) << senderID
        << "   pktID" << setw(11) << pkt->getPacketID()
        << "   srcID" << setw(11) << pkt->getHeader()->getSrcID()
        << "   dstID" << setw(11) << pkt->getHeader()->getDstID()
        << "   preID" << setw(11) << pkt->getHeader()->getPreID()
        << "   nexID" << setw(11) << pkt->getHeader()->getNexID()
        << "   " << pkt->type()
        //  << "   msg"         << setw(11) << dynamic_cast<SDN_data_payload*>(pkt->getPayload())->getMsg()
        << endl;
    // cout << pkt->type()
    //      << "   time "       << setw(11) << event::getCurTime() 
    //      << "   senID "      << setw(11) << senderID
    //      << "   pktID"       << setw(11) << pkt->getPacketID()
    //      << "   srcID "      << setw(11) << pkt->getHeader()->getSrcID() 
    //      << "   dstID"       << setw(11) << pkt->getHeader()->getDstID() 
    //      << "   preID"       << setw(11) << pkt->getHeader()->getPreID()
    //      << "   nexID"       << setw(11) << pkt->getHeader()->getNexID()
    //      << endl;
}

////////////////////////////////////////////////////////////////////////////////

class SDN_data_pkt_gen_event : public event{
public:
    class gen_data; // forward declaration

private:
    SDN_data_pkt_gen_event(SDN_data_pkt_gen_event &){}
    SDN_data_pkt_gen_event(){} // we don't allow users to new a recv_event by themselves
    // this constructor cannot be directly called by users; only by generator
    usint src; // the src
    usint dst; // the dst 
    // packet *pkt; // the packet
    string msg;

protected:
    SDN_data_pkt_gen_event(usint _trigger_time, void *data) : event(_trigger_time), src(BROCAST_ID), dst(BROCAST_ID){
        pkt_gen_data *data_ptr = (pkt_gen_data *)data;
        src = data_ptr->src_id;
        dst = data_ptr->dst_id;
        // pkt = data_ptr->_pkt;
        msg = data_ptr->msg;
    }

public:
    virtual ~SDN_data_pkt_gen_event(){}
    // SDN_data_pkt_gen_event will trigger the packet gen function
    virtual void trigger();

    usint event_priority() const;

    class SDN_data_pkt_gen_event_generator;
    friend class SDN_data_pkt_gen_event_generator;
    // SDN_data_pkt_gen_event_generator is derived from event_generator to generate an event
    class SDN_data_pkt_gen_event_generator : public event_generator{
        static SDN_data_pkt_gen_event_generator sample;
        // this constructor is only for sample to register this event type
        SDN_data_pkt_gen_event_generator(){ /*cout << "send_event registered" << endl;*/ register_event_type(&sample); }
    protected:
        virtual event *generate(usint _trigger_time, void *data){
            // cout << "send_event generated" << endl; 
            return new SDN_data_pkt_gen_event(_trigger_time, data);
        }

    public:
        virtual string type(){ return "SDN_data_pkt_gen_event"; }
        ~SDN_data_pkt_gen_event_generator(){}
    };
    // this class is used to initialize the SDN_data_pkt_gen_event
    class pkt_gen_data{
    public:
        usint src_id;
        usint dst_id;
        string msg;
        // packet *_pkt;
    };

    void print() const;
};
SDN_data_pkt_gen_event::SDN_data_pkt_gen_event_generator SDN_data_pkt_gen_event::SDN_data_pkt_gen_event_generator::sample;

void SDN_data_pkt_gen_event::trigger(){
    if(node::id_to_node(src) == nullptr){
        cerr << "SDN_data_pkt_gen_event error: no node " << src << "!" << endl;
        return;
    }
    else if(dst != BROCAST_ID && node::id_to_node(dst) == nullptr){
        cerr << "SDN_data_pkt_gen_event error: no node " << dst << "!" << endl;
        return;
    }

    SDN_data_packet *pkt = dynamic_cast<SDN_data_packet *> (packet::packet_generator::generate("SDN_data_packet"));
    if(pkt == nullptr){
        cerr << "packet type is incorrect" << endl; return;
    }
    SDN_data_header *hdr = dynamic_cast<SDN_data_header *> (pkt->getHeader());
    SDN_data_payload *pld = dynamic_cast<SDN_data_payload *> (pkt->getPayload());

    if(hdr == nullptr){
        cerr << "header type is incorrect" << endl; return;
    }
    if(pld == nullptr){
        cerr << "payload type is incorrect" << endl; return;
    }

    hdr->setSrcID(src);
    hdr->setDstID(dst);
    hdr->setPreID(src); // this column is not important when the packet is first received by the src (i.e., just generated)
    hdr->setNexID(src); // this column is not important when the packet is first received by the src (i.e., just generated)

    pld->setMsg(msg);

    recv_event::recv_data e_data;
    e_data.s_id = src;
    e_data.r_id = src; // to make the packet start from the src
    e_data._pkt = pkt;

    recv_event *e = dynamic_cast<recv_event *> (event::event_generator::generate("recv_event", trigger_time, (void *)&e_data));

}
usint SDN_data_pkt_gen_event::event_priority() const{
    string string_for_hash;
    string_for_hash = to_string(getTriggerTime()) + to_string(src) + to_string(dst); //to_string (pkt->getPacketID());
    return get_hash_value(string_for_hash);
}
// the SDN_data_pkt_gen_event::print() function is used for log file
void SDN_data_pkt_gen_event::print() const{
    cout << "time " << setw(11) << event::getCurTime()
        << "        " << setw(11) << " "
        << "        " << setw(11) << " "
        << "   srcID" << setw(11) << src
        << "   dstID" << setw(11) << dst
        << "        " << setw(11) << " "
        << "        " << setw(11) << " "
        << "   SDN_data_packet generating"
        << endl;
}

class SDN_ctrl_pkt_gen_event : public event{
public:
    class gen_data; // forward declaration

private:
    SDN_ctrl_pkt_gen_event(SDN_ctrl_pkt_gen_event &){}
    SDN_ctrl_pkt_gen_event(){} // we don't allow users to new a recv_event by themselves
    // this constructor cannot be directly called by users; only by generator
    usint src; // the src
    usint dst; // the dst 
    usint mat;
    usint act;
    // packet *pkt; // the packet
    string msg;

protected:
    SDN_ctrl_pkt_gen_event(usint _trigger_time, void *data) : event(_trigger_time), src(BROCAST_ID), dst(BROCAST_ID){
        pkt_gen_data *data_ptr = (pkt_gen_data *)data;
        src = data_ptr->src_id;
        dst = data_ptr->dst_id;
        // pkt = data_ptr->_pkt;
        mat = data_ptr->mat_id;
        act = data_ptr->act_id;
        msg = data_ptr->msg;
    }

public:
    virtual ~SDN_ctrl_pkt_gen_event(){}
    // SDN_ctrl_pkt_gen_event will trigger the packet gen function
    virtual void trigger();

    usint event_priority() const;

    class SDN_ctrl_pkt_gen_event_generator;
    friend class SDN_ctrl_pkt_gen_event_generator;
    // SDN_ctrl_pkt_gen_event_generator is derived from event_generator to generate an event
    class SDN_ctrl_pkt_gen_event_generator : public event_generator{
        static SDN_ctrl_pkt_gen_event_generator sample;
        // this constructor is only for sample to register this event type
        SDN_ctrl_pkt_gen_event_generator(){ /*cout << "send_event registered" << endl;*/ register_event_type(&sample); }
    protected:
        virtual event *generate(usint _trigger_time, void *data){
            // cout << "send_event generated" << endl; 
            return new SDN_ctrl_pkt_gen_event(_trigger_time, data);
        }

    public:
        virtual string type(){ return "SDN_ctrl_pkt_gen_event"; }
        ~SDN_ctrl_pkt_gen_event_generator(){}
    };
    // this class is used to initialize the SDN_ctrl_pkt_gen_event
    class pkt_gen_data{
    public:
        usint src_id; // the controller
        usint dst_id; // the node that should update its rule
        usint mat_id; // the target of the rule
        usint act_id; // the next hop toward the target recorded in the rule
        string msg;
        // packet *_pkt;
    };

    void print() const;
};
SDN_ctrl_pkt_gen_event::SDN_ctrl_pkt_gen_event_generator SDN_ctrl_pkt_gen_event::SDN_ctrl_pkt_gen_event_generator::sample;

void SDN_ctrl_pkt_gen_event::trigger(){
    if(dst == BROCAST_ID || node::id_to_node(dst) == nullptr){
        cerr << "SDN_ctrl_pkt_gen_event error: no node " << dst << "!" << endl;
        return;
    }

    SDN_ctrl_packet *pkt = dynamic_cast<SDN_ctrl_packet *> (packet::packet_generator::generate("SDN_ctrl_packet"));
    if(pkt == nullptr){
        cerr << "packet type is incorrect" << endl; return;
    }
    SDN_ctrl_header *hdr = dynamic_cast<SDN_ctrl_header *> (pkt->getHeader());
    SDN_ctrl_payload *pld = dynamic_cast<SDN_ctrl_payload *> (pkt->getPayload());

    if(hdr == nullptr){
        cerr << "header type is incorrect" << endl; return;
    }
    if(pld == nullptr){
        cerr << "payload type is incorrect" << endl; return;
    }

    hdr->setSrcID(src);
    hdr->setDstID(dst);
    hdr->setPreID(src);
    hdr->setNexID(src); // in hw3, you should set NexID to src
    // payload
    pld->setMsg(msg);
    pld->setMatID(mat);
    pld->setActID(act);

    recv_event::recv_data e_data;
    e_data.s_id = src;
    e_data.r_id = src; // in hw3, you should set r_id it src
    e_data._pkt = pkt;

    recv_event *e = dynamic_cast<recv_event *> (event::event_generator::generate("recv_event", trigger_time, (void *)&e_data));
}
usint SDN_ctrl_pkt_gen_event::event_priority() const{
    string string_for_hash;
    string_for_hash = to_string(getTriggerTime()) + to_string(src) + to_string(dst) + to_string(mat) + to_string(act); //to_string (pkt->getPacketID());
    return get_hash_value(string_for_hash);
}
// the SDN_ctrl_pkt_gen_event::print() function is used for log file
void SDN_ctrl_pkt_gen_event::print() const{
    cout << "time " << setw(11) << event::getCurTime()
        << "        " << setw(11) << " "
        << "        " << setw(11) << " "
        << "   srcID" << setw(11) << src
        << "   dstID" << setw(11) << dst
        << "   matID" << setw(11) << mat
        << "   actID" << setw(11) << act
        << "   SDN_ctrl_packet generating"
        << endl;
}

class SDN_stat_pkt_gen_event : public event{
public:
    class gen_data; // forward declaration

private:
    SDN_stat_pkt_gen_event(SDN_stat_pkt_gen_event &){}
    SDN_stat_pkt_gen_event(){} // we don't allow users to new a recv_event by themselves
    // this constructor cannot be directly called by users; only by generator
    usint src; // the src
    usint dst; // the dst 
    usint root;
    map <usint, usint> nei;
    // packet *pkt; // the packet
    string msg;

protected:
    SDN_stat_pkt_gen_event(usint _trigger_time, void *data) : event(_trigger_time), src(BROCAST_ID), dst(BROCAST_ID){
        pkt_gen_data *data_ptr = (pkt_gen_data *)data;
        src = data_ptr->src_id;
        dst = data_ptr->dst_id;
        // pkt = data_ptr->_pkt;
        // mat = data_ptr->mat_id;
        // act = data_ptr->act_id;
        root = data_ptr->root_id;
        nei = data_ptr->nei_list;
        msg = data_ptr->msg;
    }

public:
    virtual ~SDN_stat_pkt_gen_event(){}
    // SDN_stat_pkt_gen_event will trigger the packet gen function
    virtual void trigger();

    usint event_priority() const;

    class SDN_stat_pkt_gen_event_generator;
    friend class SDN_stat_pkt_gen_event_generator;
    // SDN_stat_pkt_gen_event_generator is derived from event_generator to generate an event
    class SDN_stat_pkt_gen_event_generator : public event_generator{
        static SDN_stat_pkt_gen_event_generator sample;
        // this constructor is only for sample to register this event type
        SDN_stat_pkt_gen_event_generator(){ /*cout << "send_event registered" << endl;*/ register_event_type(&sample); }
    protected:
        virtual event *generate(usint _trigger_time, void *data){
            // cout << "send_event generated" << endl; 
            return new SDN_stat_pkt_gen_event(_trigger_time, data);
        }

    public:
        virtual string type(){ return "SDN_stat_pkt_gen_event"; }
        ~SDN_stat_pkt_gen_event_generator(){}
    };
    // this class is used to initialize the SDN_stat_pkt_gen_event
    class pkt_gen_data{
    public:
        usint src_id; // the controller
        usint dst_id; // the node that should update its rule
        usint root_id;
        map <usint, usint> nei_list;
        string msg;
        // packet *_pkt;
    };

    void print() const;
};
SDN_stat_pkt_gen_event::SDN_stat_pkt_gen_event_generator SDN_stat_pkt_gen_event::SDN_stat_pkt_gen_event_generator::sample;

void SDN_stat_pkt_gen_event::trigger(){
    if(dst == BROCAST_ID || node::id_to_node(dst) == nullptr){
        cerr << "SDN_stat_pkt_gen_event error: no node " << dst << "!" << endl;
        return;
    }

    SDN_stat_packet *pkt = dynamic_cast<SDN_stat_packet *> (packet::packet_generator::generate("SDN_stat_packet"));
    if(pkt == nullptr){
        cerr << "packet type is incorrect" << endl; return;
    }
    SDN_stat_header *hdr = dynamic_cast<SDN_stat_header *> (pkt->getHeader());
    SDN_stat_payload *pld = dynamic_cast<SDN_stat_payload *> (pkt->getPayload());

    if(hdr == nullptr){
        cerr << "header type is incorrect" << endl; return;
    }
    if(pld == nullptr){
        cerr << "payload type is incorrect" << endl; return;
    }

    hdr->setSrcID(src);
    hdr->setDstID(dst);
    hdr->setPreID(src);
    hdr->setNexID(src); // in hw3, you should set NexID to src
    // payload
    pld->setMsg(msg);
    pld->setRootID(root);
    pld->setNeiList(nei);

    recv_event::recv_data e_data;
    e_data.s_id = src;
    e_data.r_id = src; // in hw3, you should set r_id it src
    e_data._pkt = pkt;

    recv_event *e = dynamic_cast<recv_event *> (event::event_generator::generate("recv_event", trigger_time, (void *)&e_data));
}
usint SDN_stat_pkt_gen_event::event_priority() const{
    string string_for_hash;
    string_for_hash = to_string(getTriggerTime()) + to_string(src) + to_string(dst) + to_string(root); //to_string (pkt->getPacketID());
    return get_hash_value(string_for_hash);
}
// the SDN_stat_pkt_gen_event::print() function is used for log file
void SDN_stat_pkt_gen_event::print() const{
    cout << "time " << setw(11) << event::getCurTime()
        << "        " << setw(11) << " "
        << "        " << setw(11) << " "
        << "   srcID" << setw(11) << src
        << "   dstID" << setw(11) << dst
        << "        " << setw(11) << " "
        << "        " << setw(11) << " "
        << "   SDN_stat_packet generating"
        << endl;
}

////////////////////////////////////////////////////////////////////////////////

class link{
    // all links created in the program
    static map< pair<usint, usint>, link *> id_id_link_table;

    usint id1; // from
    usint id2; // to

protected:
    link(link &){} // this constructor should not be used
    link(){} // this constructor should not be used
    link(usint _id1, usint _id2) : id1(_id1), id2(_id2){ id_id_link_table[pair<usint, usint>(id1, id2)] = this; }

public:
    virtual ~link(){
        id_id_link_table.erase(pair<usint, usint>(id1, id2)); // erase the link
    }

    static link *id_id_to_link(usint _id1, usint _id2){
        return ((id_id_link_table.find(pair<usint, usint>(_id1, _id2)) != id_id_link_table.end()) ? id_id_link_table[pair<unsigned, unsigned>(_id1, _id2)] : nullptr);
    }

    virtual double getLatency() = 0; // you must implement your own latency

    static void del_link(usint _id1, usint _id2){
        pair<usint, usint> temp;
        if(id_id_link_table.find(temp) != id_id_link_table.end())
            id_id_link_table.erase(temp);
    }

    static usint getLinkNum(){ return id_id_link_table.size(); }

    class link_generator{
        // lock the copy constructor
        link_generator(link_generator &){}
        // store all possible types of link
        static map<string, link_generator *> prototypes;
    protected:
        // allow derived class to use it
        link_generator(){}
        // after you create a new link type, please register the factory of this link type by this function
        void register_link_type(link_generator *h){ prototypes[h->type()] = h; }
        // you have to implement your own generate() to generate your link
        virtual link *generate(usint _id1, usint _id2) = 0;
    public:
        // you have to implement your own type() to return your link type
        virtual string type() = 0;
        // this function is used to generate any type of link derived
        static link *generate(string type, usint _id1, usint _id2){
            if(id_id_link_table.find(pair<usint, usint>(_id1, _id2)) != id_id_link_table.end()){
                std::cerr << "duplicate link id" << std::endl; // link id is duplicated
                return nullptr;
            }
            else if(BROCAST_ID == _id1 || BROCAST_ID == _id2){
                cerr << "BROCAST_ID cannot be used" << endl;
                return nullptr;
            }
            else if(prototypes.find(type) != prototypes.end()){ // if this type derived exists 
                link *created_link = prototypes[type]->generate(_id1, _id2);
                return created_link; // generate it!!
            }
            std::cerr << "no such link type" << std::endl; // otherwise
            return nullptr;
        }
        static void print(){
            cout << "registered link types: " << endl;
            for(map<string, link::link_generator *>::iterator it = prototypes.begin(); it != prototypes.end(); it++)
                cout << it->second->type() << endl;
        }
        virtual ~link_generator(){};
    };
};
map<string, link::link_generator *> link::link_generator::prototypes;
map<pair<usint, usint>, link *> link::id_id_link_table;

void node::add_phy_neighbor(usint _id, string link_type){
    if(id == _id) return; // if the two nodes are the same...
    if(id_node_table.find(_id) == id_node_table.end()) return; // if this node does not exist
    if(phy_neighbors.find(_id) != phy_neighbors.end()) return; // if this neighbor has been added
    phy_neighbors[_id] = true;

    link::link_generator::generate(link_type, id, _id);
}
void node::del_phy_neighbor(usint _id){
    phy_neighbors.erase(_id);

}


class simple_link : public link{
protected:
    simple_link(){} // it should not be used outside the class
    simple_link(simple_link &){} // it should not be used
    simple_link(usint _id1, usint _id2) : link(_id1, _id2){} // this constructor cannot be directly called by users

public:
    virtual ~simple_link(){}
    virtual double getLatency(){ return ONE_HOP_DELAY; } // you can implement your own latency

    class simple_link_generator;
    friend class simple_link_generator;
    // simple_link is derived from link_generator to generate a link
    class simple_link_generator : public link_generator{
        static simple_link_generator sample;
        // this constructor is only for sample to register this link type
        simple_link_generator(){ /*cout << "simple_link registered" << endl;*/ register_link_type(&sample); }
    protected:
        virtual link *generate(usint _id1, usint _id2){ /*cout << "simple_link generated" << endl;*/ return new simple_link(_id1, _id2);
        }
    public:
        virtual string type(){ return "simple_link"; }
        ~simple_link_generator(){}
    };
};

simple_link::simple_link_generator simple_link::simple_link_generator::sample;


// the data_packet_event function is used to add an initial event
void data_packet_event(usint src, usint dst, usint t = 0, string msg = "default"){
    if(node::id_to_node(src) == nullptr || (dst != BROCAST_ID && node::id_to_node(dst) == nullptr)){
        cerr << "src or dst is incorrect" << endl; return;
        return;
    }

    SDN_data_pkt_gen_event::pkt_gen_data e_data;
    e_data.src_id = src;
    e_data.dst_id = dst;
    e_data.msg = msg;

    // recv_event *e = dynamic_cast<recv_event*> ( event::event_generator::generate("recv_event",t, (void *)&e_data) );
    SDN_data_pkt_gen_event *e = dynamic_cast<SDN_data_pkt_gen_event *> (event::event_generator::generate("SDN_data_pkt_gen_event", t, (void *)&e_data));
    if(e == nullptr) cerr << "event type is incorrect" << endl;
}

// the ctrl_packet_event function is used to add an initial event
void ctrl_packet_event(usint con_id, usint id, usint mat, usint act, usint t = event::getCurTime(), string msg = "default"){
    // void ctrl_packet_event (usint dst, usint t = 0, string msg = "default"){
    if(id == BROCAST_ID || node::id_to_node(id) == nullptr){
        cerr << "id is incorrect" << endl; return;
    }

    usint src = con_id;
    SDN_ctrl_pkt_gen_event::pkt_gen_data e_data;
    e_data.src_id = src;
    e_data.dst_id = id;
    e_data.mat_id = mat;
    e_data.act_id = act;
    e_data.msg = msg;

    SDN_ctrl_pkt_gen_event *e = dynamic_cast<SDN_ctrl_pkt_gen_event *> (event::event_generator::generate("SDN_ctrl_pkt_gen_event", t, (void *)&e_data));
    if(e == nullptr) cerr << "event type is incorrect" << endl;
}

void stat_packet_event(usint id, usint con_id, usint root, map <usint, usint> nei, usint t = event::getCurTime(), string msg = "default"){
    // void stat_packet_event (usint dst, usint t = 0, string msg = "default"){
    if(id == BROCAST_ID || node::id_to_node(id) == nullptr){
        cerr << "id is incorrect" << endl; return;
    }

    usint src = id;
    SDN_stat_pkt_gen_event::pkt_gen_data e_data;
    e_data.src_id = src;
    e_data.dst_id = con_id;
    e_data.root_id = root;
    e_data.nei_list = nei;
    e_data.msg = msg;

    SDN_stat_pkt_gen_event *e = dynamic_cast<SDN_stat_pkt_gen_event *> (event::event_generator::generate("SDN_stat_pkt_gen_event", t, (void *)&e_data));
    if(e == nullptr) cerr << "event type is incorrect" << endl;
}

// send_handler function is used to transmit packet p based on the information in the header
// Note that the packet p will not be discard after send_handler ()

void node::send_handler(packet *p){
    packet *_p = packet::packet_generator::replicate(p);
    send_event::send_data e_data;
    e_data.s_id = _p->getHeader()->getPreID();
    e_data.r_id = _p->getHeader()->getNexID();
    e_data._pkt = _p;
    send_event *e = dynamic_cast<send_event *> (event::event_generator::generate("send_event", event::getCurTime(), (void *)&e_data));
    if(e == nullptr) cerr << "event type is incorrect" << endl;
}

void node::send(packet *p){ // this function is called by event; not for the user
    if(p == nullptr) return;

    usint _nexID = p->getHeader()->getNexID();
    for(map<usint, bool>::iterator it = phy_neighbors.begin(); it != phy_neighbors.end(); it++){
        usint nb_id = it->first; // neighbor id

        if(nb_id != _nexID && BROCAST_ID != _nexID) continue; // this neighbor will not receive the packet

        usint trigger_time = event::getCurTime() + link::id_id_to_link(id, nb_id)->getLatency(); // we simply assume that the delay is fixed
        // cout << "node " << id << " send to node " <<  nb_id << endl;
        recv_event::recv_data e_data;
        e_data.s_id = id;    // set the sender   (i.e., preID)
        e_data.r_id = nb_id; // set the receiver (i.e., nexID)

        packet *p2 = packet::packet_generator::replicate(p);
        e_data._pkt = p2;

        recv_event *e = dynamic_cast<recv_event *> (event::event_generator::generate("recv_event", trigger_time, (void *)&e_data)); // send the packet to the neighbor
        if(e == nullptr) cerr << "event type is incorrect" << endl;
    }
    packet::discard(p);
}

// you have to write the code in recv_handler of SDN_switch
void SDN_switch::recv_handler(packet *p){
    if(p == nullptr) return;

    if(p->type() == "SDN_data_packet"){ // the switch receives a packet from the other switch
        SDN_data_packet *p2 = nullptr;
        p2 = dynamic_cast<SDN_data_packet *> (p);

        usint dst = p2->getHeader()->getDstID();
        if(dst == getNodeID()) return; // 如果已經到終點就return
        if(table.count(dst) == 0) return; // 如果table沒有這個dst的路就return

        p2->getHeader()->setPreID(getNodeID());
        p2->getHeader()->setNexID(table[dst]);
        p2->getHeader()->setDstID(dst);

        send_handler(p2);
    }
    else if(p->type() == "SDN_ctrl_packet"){ // the switch receives a packet from the controller
        SDN_ctrl_packet *p3 = nullptr;
        p3 = dynamic_cast<SDN_ctrl_packet *> (p);
        SDN_ctrl_payload *l3 = nullptr;
        l3 = dynamic_cast<SDN_ctrl_payload *> (p3 -> getPayload());

        usint Mat_ID = l3->getMatID(); // Dst_ID
        usint Act_ID = l3->getActID(); // Next_ID
        usint Con_ID = p3 -> getHeader() -> getPreID();

        table[Mat_ID] = Act_ID;

        p3 -> getHeader() -> setDstID(Con_ID);
        p3 -> getHeader() -> setNexID(Con_ID);
        p3 -> getHeader() -> setPreID(getNodeID());
        p3 -> getPayload() -> setMsg("BackHome\n");
        send_handler(p3);
    }
    else if(p->type() == "SDN_stat_packet"){
        SDN_stat_packet *p4 = nullptr;
        p4 = dynamic_cast<SDN_stat_packet *> (p);
        SDN_stat_payload *l4 = nullptr;
        l4 = dynamic_cast<SDN_stat_payload *> (p4->getPayload());

        p4 -> getHeader() -> setNexID(p4->getHeader()->getDstID());
        p4 -> getHeader() -> setPreID(getNodeID());
        p4 -> getPayload() -> setMsg("switch to ctrl stat\n");
        send_handler(p4);
    }
}

void SDN_controller::Bellman_Ford(usint dstID){
    for(auto links : data_graph){ //圖上的每一個link

        if(shortest[links.nod1] > shortest[links.nod2] + links.Val || (shortest[links.nod1] == shortest[links.nod2] + links.Val && road[{links.nod1, dstID}] > links.nod2)){
            //先判斷node2走到node1的情況。如果走這條link會使目前node1到起點的最短距離更短，或走這條link會跟目前node1到起點的最短距離一樣，但node2編號比較小就會跑進來
            SPT[{road[{links.nod1, dstID}], dstID}].erase(links.nod1);

            SPT[{links.nod2, dstID}].insert(links.nod1);


            road[{links.nod1, dstID}] = links.nod2; //將node1要走的下一個點設為node2 

            SPTflag = 0; //有變更，因此將flag設為0
            shortest[links.nod1] = shortest[links.nod2] + links.Val; //更新node1到起點的最短距離
        }

        if(shortest[links.nod2] > shortest[links.nod1] + links.Val || (shortest[links.nod2] == shortest[links.nod1] + links.Val && road[{links.nod2, dstID}] > links.nod1)){
            //因為是雙向邊，所以也要判斷從node1走到node2的情況，基本上就是上面的兩個點換位置

            SPT[{road[{links.nod2, dstID}], dstID}].erase(links.nod2);
            SPT[{links.nod1, dstID}].insert(links.nod2);


            road[{links.nod2, dstID}] = links.nod1;

            SPTflag = 0;
            shortest[links.nod2] = shortest[links.nod1] + links.Val;
        }
    }
}

void SDN_controller::Traverse(usint parent, usint Dst_ID){ //排round順序
    for(auto child : SPT[{parent, Dst_ID}]){
        round[child] = round[parent] + 1;
        Upd_Round[{Dst_ID, round[child] - 1}].push_back({child, parent});

        Traverse(child, Dst_ID);
    }
}

void SDN_controller::recv_handler(packet *p){
    if(p == nullptr) return;

    if(p->type() == "SDN_ctrl_packet"){ // the controller receives a control packet
        SDN_ctrl_packet *p3 = nullptr;
        p3 = dynamic_cast<SDN_ctrl_packet *> (p);
        SDN_ctrl_payload *l3 = nullptr;
        l3 = dynamic_cast<SDN_ctrl_payload *> (p3->getPayload());

        usint Mat_ID = l3->getMatID(); // Dst_ID
        usint Act_ID = l3->getActID(); // Next_ID

        cout << "From: " << p3->getHeader()->getPreID() << " To: " << p3->getHeader()->getDstID() << " " << p3->getPayload()->getMsg();
        cout << "Mat: " << l3->getMatID() << " Act: " << l3->getActID() << endl;

        if(p3->getHeader()->getDstID() != getNodeID()){ //要傳給switch的
            usint switch_ID = p3 -> getHeader() -> getDstID();

            update_table[{switch_ID, Mat_ID}] ++; //0沒送過是 建立initial tree為1 送出更新為3


            p3 -> getHeader() -> setNexID(p3->getHeader()->getDstID());
            p3 -> getHeader() -> setPreID(getNodeID());

            send_handler(p3);
        }
        else{ //switch發回來的
            usint switch_ID = p3 -> getHeader() -> getPreID();

            update_table[{switch_ID, Mat_ID}] ++; //建立initial tree完為2 更新完為4

            if(update_table[{switch_ID, Mat_ID}] == 4){ //如果是第二次更新
                bool upd_flag = true;

                for(usint ID = 0; ID < getNodeID(); ID++){ //看同一round的是否都更新完了
                    if(update_table[{ID, Mat_ID}] == 3) upd_flag = false;
                }

                if(upd_flag){ //更新下一round
                    upd_round[Mat_ID]++;
                    for(auto packet : Upd_Round[{Mat_ID, upd_round[Mat_ID]}]){
                        ctrl_packet_event(getNodeID(), packet.NodID, Mat_ID, packet.ActID, event::getCurTime(), "contorller upd\n");
                    }
                }
            }
        }
    }
    else if(p->type() == "SDN_stat_packet"){ // the controller receives a state packet
        SDN_stat_packet *p4 = nullptr;
        p4 = dynamic_cast<SDN_stat_packet *> (p);
        SDN_stat_payload *l4 = nullptr;
        l4 = dynamic_cast<SDN_stat_payload *> (p4->getPayload());

        usint Root_ID = l4->getRootID();                // root_ID
        usint nodes_num = getNodeID();
        map <usint, usint> Nei_List = l4->getNeiList(); // Nei_List


        for(auto NeiData : Nei_List){ //建圖
            if(data_graph.count({NeiData.NodID, Root_ID}) != 0) continue;

            data_graph[{Root_ID, NeiData.NodID}] = NeiData.Val;
        }

        dataflag++;
        if(dataflag % nodes_num == 0){ //所有點的資料都傳完了
            SPT.clear();
            road.clear();

            //最短路徑
            for(auto dstID : dsts){ //i代表第幾個終點，把每個終點當成起點走到其他點
                shortest.clear();
                shortest.resize(nodes_num, 0x3f3f3f3f); //初始化，將起點到每個點的距離設為無限大

                SPTflag = 0; //用來判斷Bellman ford有沒有繼續更新，沒有則跳出while迴圈
                shortest[dstID] = 0; //起點到起點距離為0

                while(!SPTflag){ //如果flag == 0，則代表Bellman ford還有在繼續更新
                    SPTflag = 1;
                    //Bellman ford
                    Bellman_Ford(dstID);
                }
            }
            data_graph.clear();

            // send init packet
            if(dataflag == nodes_num){
                for(auto dstID : dsts){
                    for(usint id = 0; id < nodes_num; id++){
                        if(id == dstID) continue;
                        ctrl_packet_event(getNodeID(), id, dstID, road[{id, dstID}], event::getCurTime(), "init\n");
                    }
                }
                return;
            }
            //分配round
            for(auto dstID : dsts){
                round.clear();
                round.resize(nodes_num, 0);
                Traverse(dstID, dstID);
            }

            //send Update round1
            for(auto dstID : dsts){
                for(auto packet : Upd_Round[{dstID, 0}]){
                    ctrl_packet_event(getNodeID(), packet.NodID, dstID, packet.ActID, event::getCurTime(), "Upd first\n");
                }
            }
        }
    }
}

int main(){
    usint nodes_num, links_num, insT, updT, dura;
    usint ID, nodeA, nodeB, oldW, newW;
    vector <map <usint, usint> > neighbor_List[2];
    freopen("stdout.txt", "w+", stdout); 

    // link_info link; //link的資訊
    cin >> nodes_num >> dsts_num >> links_num;
    cin >> insT >> updT >> dura;
    neighbor_List[0].resize(nodes_num);
    neighbor_List[1].resize(nodes_num);

    for(usint i = 0; i < dsts_num; i++){ //輸入各個終點
        cin >> ID;
        dsts.push_back(ID);
    }

    // read the input and generate switch nodes
    for(usint id = 0; id < nodes_num; id++){
        node::node_generator::generate("SDN_switch", id);
    }

    usint con_id = node::getNodeNum(); //con_id is the controller ID (after all switches’ ID)
    node::node_generator::generate("SDN_controller", con_id);

    // set switches' neighbors
    for(usint i = 0; i < links_num; i++){ //輸入每條link的資訊
        cin >> ID >> nodeA >> nodeB >> oldW >> newW;
        node::id_to_node(nodeA)->add_phy_neighbor(nodeB);
        node::id_to_node(nodeB)->add_phy_neighbor(nodeA);
        neighbor_List[0][nodeA][nodeB] = oldW;
        neighbor_List[1][nodeA][nodeB] = newW;
        neighbor_List[0][nodeB][nodeA] = oldW;
        neighbor_List[1][nodeB][nodeA] = newW;
        // graph.push_back(link); //把每一條link都塞進vector裡面
    }

    for(usint id = 0; id < nodes_num; id++){ //建立每個switch跟controller的連線並傳送stat packet
        node::id_to_node(con_id)->add_phy_neighbor(id);
        node::id_to_node(id)->add_phy_neighbor(con_id);
        stat_packet_event(id, con_id, id, neighbor_List[0][id], insT, "old weight\n");
        stat_packet_event(id, con_id, id, neighbor_List[1][id], updT, "new weight\n");
    }

    // generate all initial events that you want to simulate in the networks
    usint t = 0, src = 0, dst = BROCAST_ID;
    // read the input and use data_packet_event to add an initial event
    while(cin >> t >> src >> dst){
        data_packet_event(src, dst, t);
    }

    // start simulation!!
    event::start_simulate(dura);
    // event::flush_events() ;
    // cout << packet::getLivePacketNum() << endl;
    return 0;
}

