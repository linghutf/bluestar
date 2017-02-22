#ifndef __HANDLER__HH__
#define __HANDLER__HH__

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <algorithm>

#include <memory>//c++11

#include "item.hh"

class LibItem;
class Handle{
    public:
        // 从文件中读取
        Handle(){}
        // 追加到文件中
        virtual ~Handle(){}

        void init_from_file();

        void save_to_file();

        //添加
        bool add_todo(const std::string & name)
        {
            std::set<std::shared_ptr<RecordItem> >::iterator it = std::find_if(todo_records_.begin(),todo_records_.end(),[&](std::shared_ptr<RecordItem> item){
                    return item->name() == name;
                    });

            bool ret = false;
            //如果存在，返回
            if(it==todo_records_.end())
            {
                std::shared_ptr<RecordItem> sp(new RecordItem(name));
                ret = (todo_records_.insert(sp)).second;
            }
            return ret;
        }

        // 修改
        bool update_todo(const std::string & name)
        {
            std::set<std::shared_ptr<RecordItem> >::iterator it = std::find_if(todo_records_.begin(),todo_records_.end(),[&](std::shared_ptr<RecordItem> item){
                    return item->name() == name;
                    });
            bool ret = false;
            if(it!=todo_records_.end())
            {
                std::string new_name;
                //只提供修改主题
                std::cout<<"新主题:";
                std::cin>>new_name;
                // 设置名字
                (*it)->set_name(new_name);
                /*
                char c;
                do{
                    std::cout<<"是否完成(Y/N):";
                    std::cin>>c;
                }while(c!='y'||c!='n'||c!='Y'||c!='N');
                // 添加到历史中
                */
                ret =true;
            }
            return ret;
        }

        // 删除记录，移动到历史中
        bool del_todo(const std::string & name)
        {
            //trim
            std::set<std::shared_ptr<RecordItem> >::iterator it = std::find_if(todo_records_.begin(),todo_records_.end(),[&](std::shared_ptr<RecordItem> item){
                    return item->name() == name;
                    });
            bool ret = false;
            if(it!=todo_records_.end())
            {
                (*it)->set_done(true);
                // 添加到历史
                history_records_.insert(*it);
                // 删除
                todo_records_.erase(it);
                ret =true;
            }
            return ret;
        }

        void view_records()
        {
            int c;
            do{
                std::cout<<"选择记录表(1:进行中 | 2:历史):";
                std::cin>>c;
            }while(c!=2&&c!=1);

            std::set<std::shared_ptr<RecordItem> > * p;
            if(c==1)
            {
                p = &todo_records_;
            }else
            {
                p = &history_records_;
            }

            size_t n;
            size_t item_num;
            do{
                //同步位置
                n = p->size();
                std::cout<<"浏览数目(1~"<<n<<"):";
                std::cin>>item_num;
            }while(item_num>n);

            view(*p,item_num);
        }


        // --- 知识库 ---

        bool add_item(const std::string & name)
        {
            bool ret = false;
            std::set<std::shared_ptr<LibItem> >::iterator it = std::find_if(library_.begin(),library_.end(),[&](std::shared_ptr<LibItem> item){
                    return item->name() == name;
                    });
            if(it==library_.end())
            {
                std::cout<<"新热度:";
                size_t d;
                std::cin>>d;
                std::shared_ptr<LibItem> sp(new LibItem(name,d));
                library_.insert(sp);
                ret=true;
            }
            return ret;
        }

        bool update_item(const std::string & name)
        {
            bool ret = false;
            std::set<std::shared_ptr<LibItem> >::iterator it = std::find_if(library_.begin(),library_.end(),[&](std::shared_ptr<LibItem> item){
                    return item->name() == name;
                    });
            if(it!=library_.end())
            {
                (*it)->set_name(name);
                std::cout<<"新热度:";
                size_t degree;
                std::cin>>degree;
                (*it)->set_degree(degree);
                ret = true;
            }
            return ret;
        }

        void view_items()
        {
            for(auto it = library_.begin();it!=library_.end();++it)
            {
                printf("%s\n",(*it)->name().c_str());
            }
        }

    public:
        // TODO
        size_t hashcode()
        {
            return 0;
        }

        void list_all_todo()
        {
            this->view(todo_records_,todo_records_.size());
        }
    private:
        // 浏览进行中记录，按照时间顺序，最多n条
        void view(const std::set<std::shared_ptr<RecordItem> > & records, size_t item_num)
        {
            const char tip[]="主题";
            const char times[]="时间";
            printf("%12s%30s\n",tip,times);
            size_t i=0;
            for(auto iter = records.rbegin();i<item_num;++iter,++i)
            {
                printf("%12s%30s\n",(*iter)->name().c_str(),(*iter)->to_calender().c_str());
            }
        }

    private:
        std::set<std::shared_ptr<RecordItem> > todo_records_;
        std::set<std::shared_ptr<RecordItem> > history_records_;

        // 宝库
        std::set<std::shared_ptr<LibItem> > library_;

        // 更新标记,容易碰撞，使用全部写入方式

        static char * history_filename_;
        static char * todo_filename_;
        static char * library_filename_;
};

#endif
