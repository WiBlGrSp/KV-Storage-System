#include"protocol.h"
void Msg::serilize(std::string&str) 
{
    str.clear();
    int len = code_.size();
    str+=code_;
    if(len>CODE_SIZE)
    {
        str.erase(CODE_SIZE,len-CODE_SIZE);
        printf("CODE OUT OF RANGE\n");
    }else if(len < CODE_SIZE)
    {
        str.append('\0',CODE_SIZE-len);
    }
    str+=content_;
}
void Msg::deserilize(const std::string&str) 
{
    if(str.size()<CODE_SIZE)
    {
        code_ = str;
        code_.append('\0',CODE_SIZE-str.size());
        return;
    }else if(str.size()==CODE_SIZE)
    {
        code_ = str;
    }else
    {
        code_ =  str.substr(0,CODE_SIZE);
        content_ = str.substr(6);
    }
}