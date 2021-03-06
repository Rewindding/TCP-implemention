#include "byte_stream.hh"

#include <algorithm>
#include <iterator>
#include <stdexcept>

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t cap):capacity(cap),bytes_readed(0),bytes_writed(0),que(),end_input_(false){ 
    //DUMMY_CODE(capacity);
}

size_t ByteStream::write(const string &data) {
    size_t size = que.size();
    int cnt=min(data.size(),capacity-size);
    cnt=max(cnt,0);
    for(int i=0;i<cnt;++i){
        que.push_back(data[i]);
    }
    bytes_writed+=cnt;
    return cnt;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    //如果len大于了size，做什么操作？没有明确要求
    string res;
    size_t l=min(que.size(),len);
    for(size_t i=0;i<l;++i){
        res+=que[i];
    }
    //在const函数中调用了非const函数，会出现不兼容的类型限定符错误
    return res;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) { 
    size_t l=min(len,que.size());
    for(size_t i=0;i<l;++i){
        que.pop_front();
    }
    bytes_readed+=l;
}

void ByteStream::end_input() {
    //wtf?? what should i do here?
    end_input_=1;
}

bool ByteStream::input_ended() const { 
    return end_input_;
}

size_t ByteStream::buffer_size() const { 
    return que.size(); 
}

bool ByteStream::buffer_empty() const { 
    return que.size()==0; 
}

bool ByteStream::eof() const { return input_ended()&&buffer_empty(); }

size_t ByteStream::bytes_written() const {
    return bytes_writed; 
}

size_t ByteStream::bytes_read() const { 
    return bytes_readed; 
}

size_t ByteStream::remaining_capacity() const { 
    return capacity-que.size();
}
