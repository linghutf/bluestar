#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <memory>

#include <sqlite3.h>

class Utils{
    public:
        static size_t datetime_to_unix(std::string const & str)
        {
            struct tm time;
            size_t unixtime = 0;
            strptime(str.c_str(),"%Y-%m-%d",&time);
            unixtime = (size_t)mktime(&time);
            return unixtime;
        }

        static std::string datetime_to_unix_str(std::string const & str)
        {
            char time[32];
            snprintf(time,32,"%lu",datetime_to_unix(str));
            return time;
        }

        static std::string unix_to_datetime_str(size_t n)
        {
            struct tm t = *localtime((time_t*)&n);
            char s[16];
            strftime(s,16,"%Y-%m-%d",&t);
            s[15]='\0';
            return s;
        }

        static bool isNull(std::string const & str)
        {
            return str == "";
        }

        static bool isNull(const char * str)
        {
            return str == NULL || strlen(str) == 0;
        }

        static bool isLeapYear(int y)
        {
            return (y%4==0&&y%100!=0)||(y%400==0);
        }

        static std::string get_cur_mon_datetime()
        {
            time_t now = time(0);
            struct tm *t = localtime(&now);
            char buf[11];
            t->tm_mday=1;
            strftime(buf,11,"%Y-%m-%d",t);
            buf[10]='\0';
            return buf;
        }

        // 获取当前月份第一天的unix时间戳
        static size_t get_cur_mon_unix()
        {
            time_t now = time(0);
            struct tm *t = localtime(&now);
            t->tm_mday = 1;
            time_t first = mktime(t);
            return *(size_t*)&first;
        }
};

class Item{
    public:
        Item():flag_(false){}
        Item(const char * name, int degree):
            name_(name),degree_(degree)
        {
            cur_date_ = Utils::get_cur_mon_datetime();
        }
        Item(const char * name, int degree, const char * cur_date):
            name_(name),degree_(degree),flag_(false),cur_date_(cur_date){}

        const std::string & name() const {return name_;}
        int degree() const {return degree_;}
        const std::string & cur_date() const {return cur_date_;}

        void set_name(std::string const & name){name_=name;}
        void set_degree(int d){degree_=d;}
        void flip()
        {
            flag_= !flag_;
        }

    private:
        std::string name_;
        int degree_;
        bool flag_;
        std::string cur_date_;
};

class Movie{
    public:
        Movie():
            topic_flag_(false),actor_flag_(false),pressDate_flag_(false),finishDate_flag_(false)
        {}

        Movie(const char * topic, const char * actor, const char * pressDate):
            topic_(topic),actor_(actor),pressDate_(pressDate),finishDate_("1970-01-01"),
            finishDate_flag_(false)
    {
        topic_flag_ = !Utils::isNull(topic_);
        actor_flag_ = !Utils::isNull(actor_);
        pressDate_flag_ = !Utils::isNull(pressDate_);
    }

        Movie(const char * topic, const char * actor, const char * pressDate,const char * finishDate):
            topic_(topic),actor_(actor),pressDate_(pressDate),finishDate_(finishDate),
            topic_flag_(true),actor_flag_(true),pressDate_flag_(true),finishDate_flag_(true)
    {}

        Movie(std::string & topic,std::string & actor, std::string & pressDate):
            topic_(topic),actor_(actor),pressDate_(pressDate),finishDate_("1970-01-01"),
            topic_flag_(true),actor_flag_(true),pressDate_flag_(true),finishDate_flag_(false)
    {}

        Movie(std::string & topic,std::string & actor, std::string & pressDate,std::string & finishDate):
            topic_(topic),actor_(actor),pressDate_(pressDate),finishDate_(finishDate),
            topic_flag_(true),actor_flag_(true),pressDate_flag_(true),finishDate_flag_(true)
    {}


        const std::string & topic() const {return topic_;}
        const std::string & actor() const {return actor_;}
        const std::string & press_date() const {return pressDate_;}
        const std::string & finish_date() const {return finishDate_;}

        void set_topic(std::string & topic){topic_=topic;topic_flag_=true;}
        void set_actor(std::string & actor){actor_=actor;actor_flag_=true;}
        void set_press_date(std::string & pressDate){pressDate_ = pressDate;pressDate_flag_=true;}
        void set_finish_date(std::string & finishDate){finishDate_ = finishDate;finishDate_flag_=true;}


        bool has_topic() const {return topic_flag_;}
        bool has_actor() const {return actor_flag_;}
        bool has_press_date() const {return pressDate_flag_;}
        bool has_finish_date() const {return finishDate_flag_;}


        friend std::ostream& operator<<(std::ostream& os,Movie & m)
        {
            os<<std::setw(-16)<<m.topic_;
            os<<std::setw(32)<<m.actor_;
            size_t n;
            sscanf(m.pressDate_.c_str(),"%lu",&n);
            os<<std::setw(48)<<Utils::unix_to_datetime_str(n);
            return os;
        }

    private:
        std::string topic_;
        std::string actor_;
        std::string pressDate_;
        std::string finishDate_;
        bool topic_flag_;
        bool actor_flag_;
        bool pressDate_flag_;
        bool finishDate_flag_;
};

class DataBase{
    public:
        DataBase(const char * db_name)
            :db_name_(db_name),zErrMsg_(NULL){}

        void intt()
        {
            int rc = sqlite3_open(db_name_.c_str(),&db_);
            if(rc)
            {
                fprintf(stderr,"cannot open database %s\n", sqlite3_errmsg(db_));
                //sqlite3_close(db_);
            }
        }

        // 添加未完成主题
        void insert(const Movie & m);
        // 填写完成日期，使之过期
        void drop(const Movie & m);
        // 查找当月一定数量的未完成任务
        void list_all_tasks(std::string const & date, int num, std::vector<std::shared_ptr<Movie> > *result);

        // 废弃
        void add(std::string const &topic,std::string const &actor,std::string const &pressDate);
        // 搜索主题
        void search(std::string const &topic);

        virtual ~DataBase()
        {
            sqlite3_close(db_);
        }

        // 将所有非当前月份完成的项重新调整为未完成
        void update_items()
        {
            size_t cur = Utils::get_cur_mon_unix();
            char sql[256];
            snprintf(sql,256,"update library set curDate = %lu,watch_type=0  where watch_type == 1 AND curDate!=%lu;",cur,cur);
            int rc = sqlite3_exec(db_,sql,0,0,&zErrMsg_);
            if(rc)
            {
                fprintf(stderr,"%s\n",zErrMsg_);
            }
        }
        // 判断当前月未完成的系列
        void list_todo_items(const std::string & date,std::vector<std::string> * topics)
        {
            if(topics==NULL) return;
            std::string sql = "SELECT topic from library WHERE curDate==strftime('%s','"+date+"') and watch_type == 0 ORDER BY degree desc;";
            int row,col;
            char **result;
            int rc = sqlite3_get_table(db_,sql.c_str(),&result,&row,&col,&zErrMsg_);
            if(rc)
            {
                fprintf(stderr,"%s\n",zErrMsg_);
                return;
            }
            for(int i=1;i<=row;++i)
            {
                topics->push_back(result[i*col]);
                delete result[i*col];
            }
            delete result;
        }

        // 已完成系列
        void finish_item(const std::string & name)
        {
            std::string sql = "UPDATE library set watch_type=1 where topic='"+name+"';";
            int rc = sqlite3_exec(db_,sql.c_str(),0,0,&zErrMsg_);
            if(rc)
            {
                fprintf(stderr,"%s\n",zErrMsg_);
            }
        }

        // 添加新系列
        void add_item(const Item & item)
        {
            char sql[256];
            int d = item.degree();
            snprintf(sql,256,"INSERT INTO library values('%s',%d,%d,strftime('%%s','%s'));",item.name().c_str(),0,d,item.cur_date().c_str());
            int rc = sqlite3_exec(db_,sql,0,0,&zErrMsg_);
            if(rc)
            {
                fprintf(stderr,"%s\n",zErrMsg_);
            }
        }

    private:
        std::string db_name_;
        sqlite3 *db_;
        char *zErrMsg_;
};

void DataBase::insert(const Movie & m)
{
    std::string sql;
    if(m.has_finish_date())
    {
        sql = "INSERT INTO movie values('"+m.topic()+"','"+m.actor()+"',"+Utils::datetime_to_unix_str(m.press_date())
            +","+Utils::datetime_to_unix_str(m.finish_date())+");";
    }else{
        sql = "INSERT INTO movie values('"+m.topic()+"','"+m.actor()+"',"+Utils::datetime_to_unix_str(m.press_date())
            +",0);";
    }
    std::cerr<<sql<<"\n";
    int rc = sqlite3_exec(db_,sql.c_str(),0,0,&zErrMsg_);
    if(rc){
        fprintf(stderr,"add_result:%s\n",zErrMsg_);
    }
}

void DataBase::add(std::string const &topic,std::string const &actor,std::string const &pressDate)
{
    std::string sql="insert into movie(topic,actor,pressDate) values('"+
        topic+"','"+actor+"',strftime(\"%s\",'"+pressDate+"'));";
    int rc = sqlite3_exec(db_,sql.c_str(),0,0,&zErrMsg_);
    if(rc){
        fprintf(stderr,"add_result:%s\n",zErrMsg_);
    }
}

void DataBase::drop(const Movie & m)
{
    if(!m.has_finish_date())
    {
        fprintf(stderr,"must have finished date!\n");
        return;
    }

    std::string sql = "UPDATE movie set finishDate = " +Utils::datetime_to_unix_str(m.finish_date())+" WHERE ";

    if(m.has_topic())
    {
        sql += "topic = '"+m.topic() +"';";
        //std::cerr<<sql<<std::endl;
        int rc = sqlite3_exec(db_,sql.c_str(),0,0,&zErrMsg_);
        if(rc)
        {
            fprintf(stderr,"del_result:%s\n",zErrMsg_);
        }
    }else if(m.has_press_date())
    {

    }
}

void DataBase::list_all_tasks(std::string const & date, int num, std::vector<std::shared_ptr<Movie> > *result)
{
    if(result==NULL) return;
    // 默认当月
    if(Utils::isNull(date))
    {
        time_t now = time(0);
        struct tm * t = localtime(&now);
        char buf_ld[32],buf_fd[32];
        int m = t->tm_mon+1;
        int d = t->tm_mday;
        int ld,fd=1;
        switch(m)
        {
            case 1:case 3:case 5:case 7:case 8:case 10:case 12:
                ld=31;break;
            case 4:case 6:case 9:case 11:
                ld=30;break;
            case 2:
                ld = (Utils::isLeapYear(t->tm_year+1900))?29:28;
        }
        t->tm_mday = ld;
        strftime(buf_ld,11,"%Y-%m-%d",t);
        buf_ld[11]='\0';

        //snprintf(buf_fd,32,"%d-%02d-%02d",t->tm_year+1900,m,1);

        //std::cerr<<buf_ld<<"\n"<<buf_fd<<"\n";
        //std::string sfd = Utils::datetime_to_unix_str(buf_fd);
        std::string sld = Utils::datetime_to_unix_str(buf_ld);
        //std::cerr<<sld<<"\n"<<sfd<<"\n";

        char snum[16];
        snprintf(snum,16,"%d",num);
        std::string sql = "SELECT * FROM movie WHERE pressDate<="+sld+" AND finishDate == 0 ORDER BY pressDate asc limit 0,"+snum+";";

        std::cerr<<"sql:\n"<<sql<<"\n\n";
        int nrow,ncol;
        char **azResult;
        int rc = sqlite3_get_table(db_, sql.c_str(), &azResult, &nrow, &ncol, &zErrMsg_);
        if(rc)
        {
            fprintf(stderr,"search_result:%s\n",zErrMsg_);
        }else
        {
            int i=0;
            for(int j=0;j<ncol;++j)
            {
                printf("%-18s",azResult[i*ncol+j]);
            }
            printf("\n");
            for(i=1;i<=nrow;++i)
            {
                std::shared_ptr<Movie> sp(new Movie(azResult[i*ncol],
                            azResult[i*ncol+1],
                            azResult[i*ncol+2]));
                result->push_back(sp);
                /*
                for(int j=0;j<ncol;++j)
                {
                    printf("%-18s",azResult[i*ncol+j]);
                }
                */
            }
            //delete azResult;
        }

    }
}

void DataBase::search(const std::string & topic)
{
    int nrow=0,ncol=0;
    char **azResult;
    std::string sql = "select * from movie where topic='"+topic+"';";
    // 包含表头一行的数据
    int rc = sqlite3_get_table(db_, sql.c_str(), &azResult, &nrow, &ncol, &zErrMsg_);
    if(rc)
    {
        fprintf(stderr,"search_result:%s\n",zErrMsg_);
    }else
    {
        int i=0;
        for(int j=0;j<ncol;++j)
        {
            printf("%-18s",azResult[i*ncol+j]);
            //delete azResult[i*ncol+j];
        }
        printf("\n");
        for(i=1;i<=nrow;++i)
        {
            for(int j=0;j<ncol;++j)
            {
                printf("%-18s",azResult[i*ncol+j]);
                //delete azResult[i*ncol+j];
            }
        }
        printf("\n");
        //delete azResult;
    }
}

void show_todos( DataBase & db)
{
    std::string date = Utils::get_cur_mon_datetime();
    std::vector<std::string> topics;
    db.list_todo_items(date,&topics);
    std::cout<<"系列主题:\n";
    for(auto it = topics.begin();it!=topics.end();++it)
    {
        std::cout<<*it<<"\n";
    }
}

int main(int argc, char *argv[])
{
    DataBase db("mylib.db");
    db.intt();
    db.update_items();

    // 根据参数不同调用不同函数
    if(argc==4)
    {
        if(strncmp("drop",argv[1],4)==0)
        {
            Movie m;
            std::string topic = argv[2];
            std::string date = argv[3];
            m.set_topic(topic);
            m.set_finish_date(date);
            db.drop(m);
        }
        else if(strncmp("item",argv[1],4)==0)
        {
            if(strncmp("drop",argv[2],4)==0)
            {
                db.finish_item(argv[3]);
            }
        }
        else if(strncmp("add",argv[1],3)==0)
        {
            // 提供不具名的主题插入方式
            // add xxx 2017-02-21
            Movie m(argv[2],"unknown",argv[3]);
            db.insert(m);
        }

    }else if(argc==2)
    {
        if(strncmp("list",argv[1],4)==0)
        {
            std::vector<std::shared_ptr<Movie> > list;

            db.list_all_tasks("",10,&list);

            for(auto it = list.begin();it!=list.end();++it)
            {
                std::cout<<*(*it)<<"\n";
            }

        }

    }else if(argc==5)
    {
        if(strncmp("add",argv[1],3)==0)
        {
            // add topic actor 2017-03-16
            Movie m(argv[2],argv[3],argv[4]);
            db.insert(m);
        }
        else if(strncmp("item",argv[1],4)==0)
        {
            if(strncmp("add",argv[2],3)==0)
            {
                // item add name degree
                Item item(argv[3],atoi(argv[4]));
                db.add_item(item);
            }
        }
    }else if(argc==3)
    {
        if(strncmp("item",argv[1],4)==0)
        {
            // item list
            if(strncmp("list",argv[2],4)==0)
            {
                show_todos(db);
            }
        }else if(strncmp("find",argv[1],4)==0)
        {
            // 查找信息
            db.search(argv[2]);
        }
    }
    return 0;
}

