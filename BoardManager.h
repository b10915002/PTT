#pragma once
#include <vector>
#include "json.hpp"
#include <fstream>
#include "Board.h"
#include "Viewer.h"
#include "User.h"
#include "Post.h"
#include "Admin.h"
#include "Keys.h"
using namespace std;
using json = nlohmann::json;

class BoardManager
{
public:
    enum BoardState
    {

        MENU,

        SELECT_BOARD,

        BOARD,

        POST

    };

private:
    BoardState state;
    int currentUser;
    int currentPage;
    int currentRow;
    int currentBoard;
    int currentPost;
    vector<int> lastBoard;
    string account, password;

public:
    BoardManager();
    std::vector<User *> users;
    std::vector<Board> boards;
    std::vector<Post> posts;

    void setState(BoardState);
    BoardState getState();
    void setCurrentUser(int);
    int getCurrentUser();
    void setCurrentPage(int);
    int getCurrentPage();
    void setCurrentRow(int);
    int getCurrentRow();
    void setCurrentBoard(int);
    int getCurrentBoard();
    void setCurrentPost(int);
    int getCurrentPost();
    void setLastBoardPushBack(int);
    void setLastBoardPopBack();
    int getLastBoard();
    string getCurrentAccount();
    void Start();
    void initBoards();
    void insertBoard(string, string, int);
    void deleteBoard(int);
    void initUsers();
    void insertUser(string, string, string);
    void initPosts();
    void deletePosts(int);
    void deletePosts(int, string);
    void insertPush(string, string, int);
    void deletePush(int,int);
    void deletePush(int,int, string);
    Viewer viewer;

public:
    json boardJson;
    json usersJson;
    json postsJson;
};