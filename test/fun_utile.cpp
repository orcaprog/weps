// void Servers::ParceServers()
// {
//     std::vector<std::string> vec;
//     for (size_t i = 0; i < servconf.size(); i++)
//     {
//         if (servconf[i][0] == "server" || servconf[i][0] == "location" || servconf[i][0] == "}" || servconf[i][0] == "{")
//         {
//             vec.push_back(servconf[i][0]);
//         }
//     }
//     std::vector<std::string>::iterator iter;
//     std::vector<std::string>::iterator loc;
//     iter = vec.begin();
//     iter++;
//     if (iter != vec.end() && *iter != "{")
//     {
//         throw "error no open { for server \n";
//     }
//     iter++;
//     while (iter != vec.end())
//     {
//         if (*iter == "{")
//         {
//             throw "error no open\n";
//         }

//         if (*iter == "}" && iter + 1 != vec.end())
//         {
//             throw "error no close here\n";
//         }
//         loc = std::find(iter, vec.end(), "location");

//         if (loc != vec.end())
//         {
//             loc++;
//             if (loc != vec.end() && *loc != "{void Servers::ParceServers()
// {
//     std::vector<std::string> vec;
//     for (size_t i = 0; i < servconf.size(); i++)
//     {
//         if (servconf[i][0] == "server" || servconf[i][0] == "location" || servconf[i][0] == "}" || servconf[i][0] == "{")
//         {
//             vec.push_back(servconf[i][0]);
//         }
//     }
//     std::vector<std::string>::iterator iter;
//     std::vector<std::string>::iterator loc;
//     iter = vec.begin();
//     iter++;
//     if (iter != vec.end() && *iter != "{")
//     {
//         throw "error no open { for server \n";
//     }
//     iter++;
//     while (iter != vec.end())
//     {
//         if (*iter == "{")
//         {
//             throw "error no open\n";
//         }

//         if (*iter == "}" && iter + 1 != vec.end())
//         {
//             throw "error no close here\n";
//         }
//         loc = std::find(iter, vec.end(), "location");

//         if (loc != vec.end())
//         {
//             loc++;
//             if (loc != vec.end() && *loc != "{")
//             {
//                 throw "error no open { for location\n";
//             }
//             loc++;
//             if (loc != vec.end() && *loc != "}")
//             {
//                 throw "error no open } for location\n";
//             }
//             loc++;
//             if (loc == vec.end() || (*loc == "}" && loc + 1 != vec.end()))
//             {
//                 throw "error for closeb\n";
//             }
//         }
//         iter = loc;
//     }
// }
// ")
// //             {
// //                 throw "error no open { for location\n";
// //             }
// //             loc++;
// //             if (loc != vec.end() && *loc != "}")
// //             {
// //                 throw "error no open } for location\n";
// //             }
// //             loc++;
// //             if (loc == vec.end() || (*loc == "}" && loc + 1 != vec.end()))
// //             {
// //                 throw "error for closeb\n";
// //             }
// //         }
// //         iter = loc;
// //     }
// // }
