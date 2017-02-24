#ifndef __ITEM__HH__
#define __ITEM__HH__

#include <stdint.h>
#include <time.h>
#include <string>
#include <map>

class RecordItem{
    public:
        RecordItem(const char * name):name_(name)
    {
        done_=false;
        time_t now;
        time(&now);
        create_time_ = now;
    }
        RecordItem(const char * name,bool done,size_t t):
            name_(name),done_(done),create_time_(t)

    {
    }
        RecordItem(const std::string & name):name_(name)
    {
        done_=false;
        time_t now;
        time(&now);
        create_time_ = now;
    }
        RecordItem(const std::string & name,bool done,size_t t):
            name_(name),done_(done),create_time_(t)
    {
    }

        const std::string& name() const {return name_;}
        void set_name(std::string & name) {name_=name;}
        bool is_done() const {return done_;}
        void set_done(bool done) {done_=done;}
        size_t create_time() const {return create_time_;}

        bool operator<(RecordItem const & item) const
        {
            return create_time_<item.create_time_;
        }

        size_t hashcode()
        {
            return std::hash<std::string>()(name_)<<4+
                done_*16+std::hash<size_t>()(create_time_);
        }

        std::string to_calender()
        {
            time_t tmp = create_time_;
            struct tm *p = localtime(&tmp);
            p->tm_year += 1900;
            ++p->tm_mon;
            char buf[80];
            snprintf(buf,80,"%04d-%02d-%02d",p->tm_year,p->tm_mon,p->tm_mday);
            return std::string(buf);
        }

    private:
        std::string name_;
        bool done_;
        size_t create_time_;
};

class LibItem{
    public:
        LibItem(const char * name,size_t degree):
            name_(name),degree_(degree){}
        LibItem(const std::string & name,size_t degree):
            name_(name),degree_(degree){}

        bool operator<(LibItem const & item) const
        {
            if(item.degree_ == degree_)
            {
                return name_<item.name_;
            }
            return degree_<item.degree_;
        }

        std::string & name() {return name_;}
        void set_name(const std::string & name){name_=name;}
        size_t degree() const {return degree_;}
        void set_degree(size_t degree) {degree_=degree;}

    private:
        std::string name_;
        size_t degree_; // 热度等级
};

#endif
