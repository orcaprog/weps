/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Servers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouassi <abouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:43:44 by abouassi          #+#    #+#             */
/*   Updated: 2024/01/25 20:13:35 by abouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Servers.hpp"

int  Servers::getLocation(std::string path)
{
    size_t i;
    for (i = 0; i < locations.size(); i++)
    {
        if (locations[i].path[0] == path)
        {
            return i;
        }
    }
    return -1;
}


int Servers::pathIsFile(std::string path)
{
    struct stat fileStat;
    if (stat(path.c_str(), &fileStat) == 0)
    {
        if (fileStat.st_mode & S_IFREG)
        {
            return 2;
        }
        else if (fileStat.st_mode & S_IFDIR)
        {
            return 3;
        }
        else
            return 4;
    }
    else
        return 0;
}

int Servers::pathExists(std::string path)
{
    struct stat fileStat;
    return stat(path.c_str(), &fileStat) == 0;
}

bool Servers::check_isdigit(std::string str)
{
    int i = 0;
    while (str[i])
    {
        if (!isdigit(str[i]))
        {
            return (0);
        }
        i++;
    }
    return (1);
}

void Servers::Printtwodom(const std::vector<std::vector<std::string> > &matrix, std::string data)
{
    for (std::vector<std::vector<std::string> >::const_iterator row = matrix.begin(); row != matrix.end(); ++row)
    {
        std::cout << data << "   :";
        for (std::vector<std::string>::const_iterator value = row->begin(); value != row->end(); ++value)
        {
            std::cout << *value << "|";
        }
        std::cout << std::endl;
    }
}

/*_____________________________________________________________*/
/*_________________________SET_________________________________*/
/*_____________________________________________________________*/

void Servers::parceIp(std::string ip)
{
    std::stringstream ss;
    ss << ip;
    std::string line;
    int net = 0;
    int len = 0;
    while (getline(ss, line, '.'))
    {
        net = std::atoi(line.c_str());
        if (line.size() > 3 || !check_isdigit(line) || net > 255 || net < 0)
        {
            throw "error invalid ip host " + ip + " \n";
        }
        len++;
    }
    if (len != 4)
        throw "error invalid ip host " + ip + " \n";
}
int Servers::checkDup(std::string der, int &index)
{
    int dup = 0;
    size_t i = 0;
    while (i < GetIndex("location"))
    {
        if (servconf[i][0] == der)
        {
            index = i;
            dup++;
        }
        if (dup > 1)
        {
            throw "Error duplicate derective \n";
        }
        i++;
    }
    return (dup);
}
void Servers::SetPorts()
{
    int i;
    int num = checkDup("listen", i);
    std::string arg;
    if (num == 0)
    {
        port.push_back(0);
        return;
    }
    if (servconf[i].size() != 2)
    {
        throw "invalid port in of the listen directive \n";
    }
    arg = servconf[i][1];
    int myport = std::atoi(arg.c_str());
    if (!check_isdigit(arg) || myport > 65535)
    {
        throw("invalid port in '" + arg + "' of the  directive \n");
    }
    port.push_back(myport);
}

void Servers::SetServerName()
{
    int i;
    int num = checkDup("server_name", i);
    std::string arg;
    if (num == 0)
    {
        server_name.push_back("");
        return;
    }
    if (servconf[i].size() != 2)
    {
        throw "invalid port  directive \n";
    }
    arg = servconf[i][1];

    // check hna laykon chi check
    server_name.push_back(arg);
}

void Servers::SetHost()
{
    int i;
    int num = checkDup("host", i);
    std::string arg;
    if (num == 0)
    {
        host.push_back("");
        
        return;
    }
    if (servconf[i].size() != 2)
    {
        throw "invalid host in  directive \n";
    }
    arg = servconf[i][1];
    parceIp(arg);
    host.push_back(arg);
}
void Servers::SetRoot()
{
    int i;
    int num = checkDup("root", i);
    std::string arg;
    if (num == 0)
    {
        root.push_back("");
        return;
    }
    if (servconf[i].size() != 2)
    {
        throw "invalid root directive \n";
    }
    arg = servconf[i][1];
    if (!pathExists(arg))
    {
        throw("Path '" + arg + "' does not exist.\n");
    }
    root.push_back(arg);
}
void Servers::SetIndex()
{
    int i;
    int num = checkDup("index", i);
    std::string arg;
    if (num == 0)
    {
        index.push_back("");
        return;
    }
    if (servconf[i].size() != 2)
    {
        throw "invalid port in of the server_name directive \n";
    }
    arg = servconf[i][1];
    // std::cout<<"index   :"<<arg<<endl;
    // if (pathIsFile(arg) != 2 )
    // {
    //     throw("Path '" + arg + "' does not exist or is not a file.\n");
    // }
    index.push_back(arg);
}
void Servers::SetClient_max_body_size()
{
    int i;
    int num = checkDup("client_max_body_size", i);
    std::string arg;
    if (num == 0)
    {
        client_max_body_size.push_back(0);
        return;
    }
    if (servconf[i].size() != 2)
    {
        throw "invalid client_max_body_size  directive \n";
    }
    arg = servconf[i][1];
    long long int body_size = std::strtod(arg.c_str(), NULL);
    if (!check_isdigit(arg))
    {
        throw "invalid port in '" + arg + "' of the  directive \n";
    }
    client_max_body_size.push_back(body_size);
}

void Servers::check_Status(std::string status)
{
    std::vector<std::string>::iterator iter;

    iter = std::find(s_erorr.begin(), s_erorr.end(), status);
    if (iter == s_erorr.end())
    {
        throw "Error : Invalid status '" + status + "' code  Derecties\n";
    }
}
std::vector<std::string> Servers::AddErrorPage(std::string status, std::string path)
{
    std::vector<std::string> vErrorPage;
    vErrorPage.push_back(status);
    vErrorPage.push_back(path);

    return vErrorPage;
}

void Servers::SetError_page()
{
    std::string status;
    std::string path;
    for (size_t i = 0; i < servconf.size(); i++)
    {
        if (servconf[i][0] == "error_page")
        {
            if (servconf[i].size() != 3)
            {
                throw "Error in error_page\n";
            }
            status = servconf[i][1];
            path = servconf[i][2];
            check_Status(status);
            if(pathIsFile(path) == 2)
                error_page[status] = path;
            else
            {
                path = root[0] +"/"+path;
                if (pathIsFile(path) != 2)
                {
                    throw "path is not file or nosush file '"+path+"'\n";
                }
                error_page[status] = path;
            }
        }
    }
}

void Servers::SetAllDir()
{
    // ParceServers();
    FillValid();
    FillStatus();
    FillLocation();
    checkValidation();

    SetHost();
    SetRoot();
    SetPorts();
    SetIndex();
    SetServerName();
    SetError_page();
    SetClient_max_body_size();

    size_t i = 0;
    while (i < locations.size())
    {
        locations[i].SetAllDir();
        i++;
    }
}
/*_____________________________________________________________*/
/*_________________________GET_________________________________*/
/*_____________________________________________________________*/

const int & Servers::GetPorts()
{
    return port[0];
}
const std::string &Servers::GetServerName()
{
    return server_name[0];
}
const std::string &Servers::GetHost()
{
    return host[0];
}
const std::string &Servers::GetRoot()
{
    return root[0];
}

const long long int &Servers::GetClient_max_body_size()
{
    return client_max_body_size[0];
}
const std::string &Servers::GetIndex()
{
    return index[0];
}

/*=======================================================================*/
/*=======================================================================*/
size_t Servers::GetIndex(std::string dir)
{
    size_t i;
    for (i = 0; i < servconf.size(); i++)
    {
        if (servconf[i][0] == dir)
        {
            return i;
        }
    }
    return (i);
}
Location Servers::FirstFill(size_t &index)
{
    Location loaction;
    loaction.vlocation.push_back(servconf[index]);
    index++;
    while (index < servconf.size() && servconf[index][0] != "location")
    {
        // std::cout<<index<<"  :"<<servconf[index][0]<<std::endl;
        loaction.vlocation.push_back(servconf[index]);
        index++;
    }
    return loaction;
}

void Servers::FillLocation()
{
    size_t index = GetIndex("location");

    if (index == servconf.size())
    {
        return;
    }
    while (index < servconf.size())
    {
        locations.push_back(FirstFill(index));
    }
}
/*=======================================================================*/
/*=======================================================================*/

void Servers::FillStatus()
{
    s_erorr.push_back("400");
    s_erorr.push_back("401");
    s_erorr.push_back("402");
    s_erorr.push_back("403");
    s_erorr.push_back("404");
    s_erorr.push_back("405");
    s_erorr.push_back("406");
    s_erorr.push_back("407");
    s_erorr.push_back("408");
    s_erorr.push_back("409");
    s_erorr.push_back("410");
    s_erorr.push_back("411");
    s_erorr.push_back("412");
    s_erorr.push_back("413");
    s_erorr.push_back("414");
    s_erorr.push_back("415");
    s_erorr.push_back("416");
    s_erorr.push_back("417");
    s_erorr.push_back("418");
    s_erorr.push_back("421");
    s_erorr.push_back("422");
    s_erorr.push_back("423");
    s_erorr.push_back("424");
    s_erorr.push_back("425");
    s_erorr.push_back("426");
    s_erorr.push_back("428");
    s_erorr.push_back("429");
    s_erorr.push_back("431");
    s_erorr.push_back("451");
    s_erorr.push_back("500");
    s_erorr.push_back("501");
    s_erorr.push_back("502");
    s_erorr.push_back("503");
    s_erorr.push_back("504");
    s_erorr.push_back("505");
    s_erorr.push_back("506");
    s_erorr.push_back("507");
    s_erorr.push_back("508");
    s_erorr.push_back("510");
    s_erorr.push_back("511");
}
void Servers::FillValid()
{
    Vstrvalid.push_back("listen");
    Vstrvalid.push_back("server");
    Vstrvalid.push_back("server_name");
    Vstrvalid.push_back("host");
    Vstrvalid.push_back("root");
    Vstrvalid.push_back("error_page");
    Vstrvalid.push_back("client_max_body_size");
    Vstrvalid.push_back("index");
    Vstrvalid.push_back("location");
    Vstrvalid.push_back("{");
    Vstrvalid.push_back("}");
    Vstrvalid.push_back("#");
    Vstrvalid.push_back("allow_methods");
    Vstrvalid.push_back("autoindex");
    Vstrvalid.push_back("upload");
    Vstrvalid.push_back("cgi_path");
}
void Servers::checkValidation()
{
    std::vector<std::string>::iterator iter;
    for (size_t i = 0; i < GetIndex("location"); i++)
    {
        iter = std::find(Vstrvalid.begin(), Vstrvalid.end(), servconf[i][0]);
        if (iter == Vstrvalid.end())
        {
            throw "Error : Invalid Derecties\n";
        }
    }
}

void Servers::desplay()
{
    // std::vector<std::vector<std::string> > matrix = servconf;

    cout<<"Ports :"<<GetPorts()<<endl;
    cout<<"ServerName  :"<<GetServerName()<<endl;
    cout<<"Host :"<<GetHost()<<endl;
    cout<<"Root :"<<GetRoot()<<endl;
    map<string,string>::iterator iter = error_page.begin();
    while (iter != error_page.end())
    {
        cout<<"error Page :'"<<iter->first<<"' '"<<iter->second<<"'\n";
        iter++;
    }
    
    cout<<"Client_max_body_size :"<<endl;
    cout<<"Index :"<<GetIndex()<<endl;
    size_t i = 0;
    while (i < locations.size())
    {
        std::cout << "________________________\n";
        locations[i].desplayLocation();
        i++;
    }
}

/*#############################################################*/
/*CREATE SOKCET*/
/*#############################################################*/

void Servers::CreatSocketServer()
{

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("connot create socket");
        return;
    }

    int reuseaddr = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(int)) == -1)
    {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port[0]);
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        return;
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("“In listen”");
        exit(EXIT_FAILURE);
    }
}
/*#############################################################*/
void Servers::SetDefaultError()
{
    error_page["400"] =  "../error_pages/400.html";
    error_page["401"] =  "../error_pages/401.html";
    error_page["402"] =  "../error_pages/402.html";
    error_page["403"] =  "../error_pages/403.html";
    error_page["404"] =  "../error_pages/404.html";
    error_page["405"] =  "../error_pages/405.html";
    error_page["406"] =  "../error_pages/406.html";
    
}
int Servers::searchPathLocation(string &uri)
{
    string pathL;
    for (size_t i = 0; i < locations.size(); i++)
    {
        pathL =  locations[i].path[0] ;
        if (!strncmp(uri.c_str(),pathL.c_str(),pathL.length())  && pathL != "/")
        {
            return i;
        }
    }
    return -1;
}

int  Servers::fillFromLocation(int &in, string &uri)
{
    size_t pos;
    pos = uri.find("?");
    int len;
    
    if (pos != std::string::npos)
    {
        len = uri.length() - pos;
        char q[len + 1];
        uri.copy(q,len,pos);
        q[len] = '\0';
        querys = q;
        uri.erase(pos,len);
    }
    if (locations[in].root[0].empty())
    {
        rootUri = uri;
        rootUri.replace(0, locations[in].path[0].length(), root[0]);
        if (pathIsFile(rootUri) == 3)
        {
            if (locations[in].index[0].empty())
            {
                rootUri += ("/" + index[0]);
            }
            else
            {
                rootUri += ("/" + locations[in].index[0]);
            }
        }
        // if (!pathExists(rootUri))
        // {
        //     // throw "Erorr in " + rootUri + ": no such file or directory";
        //     cout << "Erorr in " + rootUri + ": no such file or directory" << endl;
        //     return 0;
        // }
    }
    else
    {
        rootUri = uri;
        rootUri.replace(0, locations[in].path[0].length(), locations[in].root[0]);
        if (pathIsFile(rootUri) == 3)
        {
            if (locations[in].index[0].empty())
            {
                rootUri += ("/" + index[0]);
            }
            else
            {
                rootUri += ("/" + locations[in].index[0]);
            }
        }
        // if (!pathExists(rootUri))
        // {
        //     // throw "Erorr in " + rootUri + ": no such file or directory";
        //     cout << "Erorr in " + rootUri + ": no such file or directory" << endl;
        //     return 0;
        // }
        
    }
    return 1;
}

void Servers::FillData(string uri)
{
    int in = searchPathLocation(uri);
    Is_cgi = false;
    int def = 0;
    string LocationIndex;
    if (in == -1)
    {

        def = getLocation("/");
        if (def != -1)
        {
            if (locations[def].root[0].empty())
            {
                rootUri = root[0] + uri;
            }
            else 
                rootUri = locations[def].root[0] + uri;

            if (pathIsFile(rootUri) == 3)
            {
                LocationIndex = locations[def].index[0];
                if (LocationIndex.empty())
                    rootUri += ("/" + index[0]);
                else
                    rootUri += ("/" + LocationIndex);
            }
            UriLocation = locations[def];
            // if (!pathExists(rootUri))
            // {
            //     // throw "Erorr in " + rootUri + ": no such file or directory";
            //     cout << "Erorr in " + rootUri + ": no such file or directory" << endl;
            //     return;
            // }
        }
        else
        {
            rootUri = root[0] +uri +"/" + index[0];
            UriLocation.path.push_back("");
            UriLocation.root.push_back(root[0]);
            UriLocation.allow_methods.push_back("");
            UriLocation.autoindex = 0;
            UriLocation.upload = 0;
            UriLocation.index.push_back(index[0]);
        }
    }
    else
    {
        std::cout<<"Path of location :"<<locations[in].GetPath()<<endl;
        // if()
        // {
            fillFromLocation(in, uri);
            UriLocation = locations[in];
            if (locations[in].GetPath() == "/cgi")
            {
                Is_cgi = true;
            }
            
        // }
    }
}

Servers::Servers()
{
    // root.push_back("");
    SetDefaultError();
}

Servers::~Servers()
{
}