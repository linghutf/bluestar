#include "handler.hh"

#include <stdlib.h>
#include <string.h>
#include <sstream>

char * Handle::history_filename_ = "dat/history.rawdb";
char * Handle::todo_filename_ = "dat/todo.rawdb";
char * Handle::library_filename_ = "dat/lib.rawdb";

void Handle::init_from_file()
{
    char buf[BUFSIZ];
    std::ifstream his_fp(history_filename_,std::ios::in);
    if(!his_fp.is_open())
    {
        printf("cannot open history file!\n");
        exit(EXIT_FAILURE);
    }

    while(his_fp.getline(buf,BUFSIZ))
    {
        char name[80];
        char c;
        size_t t;
        sscanf(buf,"%s %c %lu",name,&c,&t);
        std::shared_ptr<RecordItem> sp(new RecordItem(name,c=='Y',t));
        history_records_.insert(sp);
        memset(buf,0,BUFSIZ);
    }


    std::ifstream todo_fp(todo_filename_,std::ios::in);
    if(!todo_fp.is_open())
    {
        printf("cannot open todo file!\n");
        exit(EXIT_FAILURE);
    }
    while(todo_fp.getline(buf,BUFSIZ))
    {
        char name[80];
        char c;
        size_t t;
        sscanf(buf,"%s %c %lu",name,&c,&t);
        std::shared_ptr<RecordItem> sp(new RecordItem(name,c=='Y',t));
        todo_records_.insert(sp);
        memset(buf,0,BUFSIZ);
    }

    std::ifstream lib_fp(library_filename_,std::ios::in);
    if(!lib_fp.is_open())
    {
        printf("cannot open library file!\n");
        exit(EXIT_FAILURE);
    }

    while(lib_fp.getline(buf,BUFSIZ))
    {
        char name[80];
        size_t d;
        sscanf(buf,"%s %lu",name,&d);
        std::shared_ptr<LibItem> sp(new LibItem(name,d));
        library_.insert(sp);
        memset(buf,0,BUFSIZ);
    }

    // TODO 计算Hash值，以便后期追加数据

    lib_fp.close();
    todo_fp.close();
    his_fp.close();
}

void Handle::save_to_file()
{
    std::ofstream his_fp(history_filename_,std::ios::out);
    if(his_fp.is_open())
    {
        for(auto it = history_records_.begin();it!=history_records_.end();++it)
        {
            his_fp<<(*it)->name()<<' '<<((*it)->is_done()?'Y':'N')<<' '<<(*it)->create_time()<<'\n';
        }
    }
    his_fp.close();

    std::ofstream todo_fp(todo_filename_,std::ios::out);
    if(todo_fp.is_open())
    {
        size_t n;
        for(auto it = todo_records_.begin();it!=todo_records_.end();++it)
        {
            todo_fp<<(*it)->name()<<' '<<((*it)->is_done()?'Y':'N')<<' '<<(*it)->create_time()<<'\n';
        }
    }
    todo_fp.close();


    std::ofstream lib_fp(library_filename_,std::ios::out);
    if(lib_fp.is_open())
    {
        for(auto it = library_.begin();it!=library_.end();++it)
        {
            lib_fp<<(*it)->name()<<' '<<(*it)->degree()<<'\n';
        }
    }
    lib_fp.close();
}
