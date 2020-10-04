/* This is a base application for cinolib (https://github.com/maxicino/cinolib).
 * It will show a GL canvas (and associated control panel) to interact
 * with a triangle mesh.
 *
 * In case you don't need a GUI, you can drop the "Drawable" prefix from the mesh data type.
 * What you will get is a lighter yet fully operational mesh data structure, just
 * without the burden of OpenGL code necessary for rendering!
 *
 * Enjoy!
*/

#include <QApplication>
#include <cinolib/meshes/meshes.h>
#include <cinolib/gui/qt/qt_gui_tools.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <cinolib/drawable_object.h>
#include <cinolib/drawable_sphere.h>
#include <cinolib/gl/draw_sphere.h>
#include <cinolib/geometry/vec3.h>
#include <cinolib/color.h>
#include <stack>

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

int main(int argc, char **argv)
{
    using namespace std;
    using namespace cinolib;

    QApplication a(argc, argv);
    string mesh;

    int object = 1;
    switch(object) {
      case 1:
        mesh = "/bunny.obj";
        break;
      case 2:
        mesh = "/mesh/cup.obj";
        break;
      case 3:
        mesh = "/blub_triangulated.obj";
        break;
      default:
        break;
    }
    std::string s = (argc==2) ? std::string(argv[1]) : std::string(DATA_PATH) + mesh;

//    std::string s = (argc==2) ? std::string(argv[1]) : std::string(DATA_PATH) + "/bunny.obj";
//    std::string s = (argc==2) ? std::string(argv[1]) : std::string(DATA_PATH) + "/mesh/cup.obj";
//    std::string s = (argc==2) ? std::string(argv[1]) : std::string(DATA_PATH) + "/blub_triangulated.obj";

    DrawableTrimesh<> m(s.c_str());

    // Rotation to obtain a NON-Manifold Verted in the Orange Cluster around the back of the head
    m.translate(m.bbox().center());

    switch(object) {
      case 1:
        m.rotate(vec3d(0,1,0),0.001); // for BUNNY
        break;
      case 2:
        m.rotate(vec3d(1,0,0),0.39); //for CUP
        break;
      case 3:
        m.rotate(vec3d(1,0,0),0.35); //for blub_triangulated
        break;
      default:
        break;
    }


    m.updateGL(); //Always update after transforms on mesh

    vector<DrawableSphere> points;

    /// COLORS
    /*
    // Subdivision in Cluster into the 8
    std::vector<Color> colors(8);
    colors[0] = Color::GREEN();
    colors[1] = Color::PASTEL_YELLOW();
    colors[2] = Color::YELLOW();
    colors[3] = Color::BLUE();
    colors[4] = Color::PASTEL_PINK();
    colors[5] = Color::PASTEL_CYAN();
    colors[6] = Color::PASTEL_ORANGE();
    colors[7] = Color::PASTEL_VIOLET();

    double x,y,z;
    for(uint pid=0; pid < m.num_polys(); ++pid){
        x = m.poly_centroid(pid).x();
        y = m.poly_centroid(pid).y();
        z = m.poly_centroid(pid).z();

        if(x >= 0 && y >= 0 && z >= 0) m.poly_data(pid).color = colors[0];
        if(x >= 0 && y >= 0 && z <= 0) m.poly_data(pid).color = colors[1];
        if(x >= 0 && y <= 0 && z >= 0) m.poly_data(pid).color = colors[2];
        if(x >= 0 && y <= 0 && z <= 0) m.poly_data(pid).color = colors[3];
        if(x <= 0 && y >= 0 && z >= 0) m.poly_data(pid).color = colors[4];
        if(x <= 0 && y >= 0 && z <= 0) m.poly_data(pid).color = colors[5];
        if(x <= 0 && y <= 0 && z >= 0) m.poly_data(pid).color = colors[6];
        if(x <= 0 && y <= 0 && z <= 0) m.poly_data(pid).color = colors[7];
    }

    m.updateGL();

    for(auto color: colors){
        for(uint vid = 0; vid < m.num_verts() ; ++vid){

            if( !m.vert_is_manifold(vid, color)){

                //Push sphere to GUI
                DrawableSphere sphere(m.vert(vid));
                points.push_back(sphere);

                // SPLITTING
                for(auto eid : m.vert_ordered_edges_star(vid)){
                    m.edge_split(eid, 0.5); // lambda 0.5 == split edge by the half point
                }

                m.updateGL();

                vector<uint> poly_star = m.vert_ordered_polys_star(vid);

                // Like KMP dublicate pid to simulate a circular space in which to look for occurences
                for(auto pid : m.vert_ordered_polys_star(vid)){
                    poly_star.push_back(pid);
                }
                vector<vector<uint>> separated_slices(poly_star.size());
                uint index = 0;
                cout << "PolyStar size: " + to_string(poly_star.size()) << endl;

                // POLY STAR RED MARKED
                cout << "PolyStar: " << endl;
                for(uint pid : poly_star){
                    cout << pid  << endl;
                    if(m.poly_data(pid).color != color){
                        separated_slices.at(index).push_back(pid);

    colors[4] = Color::PASTEL_PINK();        }
                    if(m.poly_data(pid).color == color)
                        ++index;
                }

                //Biggest Slice -> Tunnel
                vector<uint> &tunnel = poly_star; // Like setting initial size to infinity, to be sure to get che minimum set separated
                int aux = 0;
                for(auto &vec : separated_slices){
                    cout << "Tunnel: " + to_string(aux) + " - Size: " + to_string(vec.size())<< endl;
                    if(vec.size() < tunnel.size() && vec.size() > 0){
                        cout << "Debug" << endl;
                        cout << "Vec_Size: " + to_string(vec.size()) << endl;
                        tunnel = vec;
                    }
                    ++aux;
                }
                cout << "Tunnel  TO RE color: " << endl;
                for(auto pid : tunnel){
                    cout << pid << endl;
                }

                // Recolor Tunnel
                cout << "Recoloring PIDs: " + to_string(tunnel.size()) + " polygons"<< endl;
                for(auto pid : tunnel){
                    cout << pid << endl;
                    m.poly_data(pid).color = color;
                }
            }
        }
    }
    */

    /// LABELS

    // Subdivision in Cluster into the 8
    vector<int> labels(8);
    labels[0] = 0;
    labels[1] = 1;
    labels[2] = 2;
    labels[3] = 3;
    labels[4] = 4;
    labels[5] = 5;
    labels[6] = 6;
    labels[7] = 7;

    double x,y,z;
    for(uint pid=0; pid < m.num_polys(); ++pid){
        x = m.poly_centroid(pid).x();
        y = m.poly_centroid(pid).y();
        z = m.poly_centroid(pid).z();

        if(x >= 0 && y >= 0 && z >= 0) m.poly_data(pid).label = 0;
        if(x >= 0 && y >= 0 && z <= 0) m.poly_data(pid).label = 1;
        if(x >= 0 && y <= 0 && z >= 0) m.poly_data(pid).label = 2;
        if(x >= 0 && y <= 0 && z <= 0) m.poly_data(pid).label = 3;
        if(x <= 0 && y >= 0 && z >= 0) m.poly_data(pid).label = 4;
        if(x <= 0 && y >= 0 && z <= 0) m.poly_data(pid).label = 5;
        if(x <= 0 && y <= 0 && z >= 0) m.poly_data(pid).label = 6;
        if(x <= 0 && y <= 0 && z <= 0) m.poly_data(pid).label = 7;
    }

    m.rotate(vec3d(0,1,0),160.1); // for BUNNY

/*
    for(auto label : labels){
        for(uint vid = 0; vid < m.num_verts() ; ++vid){
            if( !m.vert_is_manifold_cluster(vid, label)){
                //Push sphere to GUI
                DrawableSphere sphere(m.vert(vid));
                points.push_back(sphere);

                // SPLITTING
                for(auto eid : m.vert_ordered_edges_star(vid)){
//                    m.edge_split(eid, 0.5); // lambda 0.5 == split edge by the half point
                }
                m.updateGL();

                cout << "Vertex adj:"  << endl;
                for(auto pid : m.adj_v2p(vid)){
                    cout << pid  << endl;
                }

                vector<uint> poly_star = m.vert_ordered_polys_star(vid);

                // Like KMP dublicate pid to simulate a circular space in which to look for occurences
                for(auto pid : m.vert_ordered_polys_star(vid)){
                    poly_star.push_back(pid);
                }
                vector<vector<uint>> separated_slices(poly_star.size());
                uint index = 0;
//                cout << "PolyStar size: " + to_string(poly_star.size()) << endl;

                // POLY STAR RED MARKED
//                cout << "PolyStar: " << endl;
                for(uint pid : poly_star){
//                    cout << pid  << endl;
                    if(m.poly_data(pid).label != label){
                        separated_slices.at(index).push_back(pid);
                    }
                    if(m.poly_data(pid).label == label)
                        ++index;
                }

                //Biggest Slice -> Tunnel
                vector<uint> &tunnel = poly_star; // Like setting initial size to infinity, to be sure to get che minimum set separated
                int aux = 0;
                for(auto &vec : separated_slices){
//                    cout << "Tunnel: " + to_string(aux) + " - Size: " + to_string(vec.size())<< endl;
                    if(vec.size() < tunnel.size() && vec.size() > 0){
//                        cout << "Debug" << endl;
//                        cout << "Vec_Size: " + to_string(vec.size()) << endl;
                        tunnel = vec;
                    }
                    ++aux;
                }
//                cout << "Tunnel  TO RE color: " << endl;
                for(auto pid : tunnel){
//                    cout << pid << endl;
                }

                // Recolor Tunnel
                cout << "Recoloring PIDs: " + to_string(tunnel.size()) + " polygons"<< endl;
                for(auto pid : tunnel){
                    cout << pid << endl;
                    m.poly_data(pid).label = label;
                }
            }
        }
    }
*/

//    auto edges = m.adj_v2e(5853);
//    for(auto eid : edges){
//        m.edge_split(eid, 0.5);
//    }
//    m.poly_data(28581).label = 5;

    uint verts = m.num_verts();
    for(uint vid = 0; vid < verts ; ++vid){
        if( !m.vert_is_manifold_cluster(vid)){

//            //Push sphere to GUI
//            DrawableSphere sphere(m.vert(vid));
//            points.push_back(sphere);

            /// Cut around with ordered
//            /*
//            auto star = m.vert_ordered_edges_star(vid);
//            for(auto eid: star){
//                m.edge_split(eid, 0.5);
//            }

//            auto polys = m.adj_v2p(vid);
//            for(auto pid : polys){
//                if(m.poly_contains_vert(pid, vid)){
//                    auto offset = m.poly_vert_offset(pid, vid);
//                    auto edges = m.poly_v2e(pid, m.poly_vert_id(pid,offset));
//                    for(auto eid: edges){
//                        m.edge_split(eid, 0.5);
//                    }
//                }
//            }

            auto edges = m.adj_v2e(vid);
            for(auto eid : edges){
                m.edge_split(eid, 0.5);
            }
//            */

            /// Cut Around WITHOUT ORDER
          /*
            std::vector<uint> e_link = m.adj_v2e(vid);
            std::unordered_set<uint> edge_set(e_link.begin(), e_link.end());

            std::queue<uint> q;
            q.push(e_link.front());

            std::unordered_set<uint> visited;
            visited.insert(e_link.front());

            while(!q.empty())
            {
                uint curr = q.front();
                q.pop();

                assert(CONTAINS(visited, curr));

                for(uint nbr : m.adj_e2e(curr))
                {
                    // still in the link of vid, but not visited yet
                    if(CONTAINS(edge_set, nbr) && !CONTAINS(visited, nbr))
                    {
                        visited.insert(nbr);
                        m.edge_split(nbr, 0.5);
                        q.push(nbr);
                    }
                }
            }
            m.edge_split(e_link.front(), 0.5);

            m.updateGL();
          */


            vector<vector<uint>> components = m.vert_poly_cc_by_labels(vid);
            unordered_map<int, int> labels;

            // Calculate Unique Labels
            for(auto comp : components){
                int curr_label = m.poly_data(comp[0]).label;
                auto query = labels.find(curr_label);
                if(query == labels.end()){
                    labels.insert(make_pair(curr_label, 1));
                }else{
                    query->second++;
                }
            }

            // Calculate number of poly of each label
            map<int, int> count_label;
            for (auto comp: components){
                for(auto pid: comp){
                    int curr_label = m.poly_data(pid).label;
                    auto query = count_label.find(curr_label);
                    if(query == count_label.end()){
                        count_label.insert(make_pair(curr_label, 1));
                    }else{
                        query->second++;
                    }
                }
            }

            // Count number of components for each label
            map<int, int> count_comp_label;
            for (auto comp: components){
                int curr_label = m.poly_data(comp[0]).label;
                auto query = count_comp_label.find(curr_label);
                if(query == count_comp_label.end()){
                    count_comp_label.insert(make_pair(curr_label, 1));
                }else{
                    query->second++;
                }
            }

            // Calculate Tunnel Start. CCs index and Label to begin
            int countMax = 0;
            int searched_label = 0;
            for(auto it = count_label.cbegin(); it != count_label.cend(); ++it ) {
                auto query = count_comp_label.find(it->first);
                auto cc_count = query->second;
                if (it->second > countMax && cc_count >= 2){
                    searched_label = it->first;
                    countMax = it->second;
                }
            }

            // Pretty print for Connected Componets
            {
                int i = 0;
                std::cout << "======================================" << std::endl;
                std::cout << "vid: " + std::__cxx11::to_string(vid)  +
                             "  -  Comp #: " + std::__cxx11::to_string(components.size()) +
                             "  -  Labels #: " + std::__cxx11::to_string(labels.size()) << std::endl;

                for (auto comp : components){
                    std::cout << "Component[" + std::__cxx11::to_string(i) + "] pids: " << std::endl;
                    for(auto pid : comp){
                        std::cout << std::__cxx11::to_string(pid) + "\t -> Label: " + std::__cxx11::to_string(m.poly_data(pid).label) << std::endl;
                    }
                    ++i;
                }
            }

            cout << "-----------------" << endl;
            cout << "Label '" << searched_label << "' occurs " << countMax << " times " << endl;

            int max_pid_count=0;
            int index = 0;
            int searched_start_comp = 0;
            for (auto comp: components ){

                if (int(comp.size()) > max_pid_count && m.poly_data(comp[0]).label == searched_label){
                    searched_start_comp = index;
                    max_pid_count = int(comp.size());
                }
                index++;
            }

            cout << "Starting Component Index = " << searched_start_comp << endl;
            cout << "CountMax = " << countMax << endl;
            cout << "======================================" << endl;

            // Exoands around vid searching for shortest route
            vector<uint> start_comp = components[uint(searched_start_comp)];
            vector<uint> contour;
            vector<uint> expand;
            for (auto pid : start_comp){
                for (auto pid2 : m.adj_p2p(pid)){
                    contour.push_back(pid2);
                }
            }
            for (auto pid : contour){
                if (CONTAINS_VEC(m.adj_v2p(vid), pid) && DOES_NOT_CONTAIN_VEC(start_comp, pid)){
                    expand.push_back(pid);
                }
            }

            // PIDs adjacent to starting component
            cout << "-----------------" << endl;
            cout << "PIDs adjacent to starting component" << endl;
            for(auto pid : expand){
                cout << pid << endl;
            }

            stack<vector<uint>> q;
            q.push(components[uint(searched_start_comp)]);

            //Visited contains all pid of poly connected to the first in the cluster
            vector<uint> to_relabel;
            vector<uint> visited;

            uint indexes_path;
            bool found = false;
            while(!found){
                auto curr = q.top();
                q.pop();
                indexes_path = 0;
                for (auto nbr : components){
                    if(nbr != curr){
                        if (m.poly_data(nbr[0]).label != searched_label){
                            q.push(nbr);
                            to_relabel.push_back(indexes_path);
                        }
                        else{
                            found = true;
                        }
                    }
                    indexes_path++;
                }
            }

            cout << "-----------------" << endl;
            cout << "Compo to Relabel" << endl;
            for(auto pid : to_relabel){
                cout << pid << endl;
            }

            int relabel_count = int(components[to_relabel[0]].size());

            index = 0;
            for(auto ind : to_relabel){
                for( auto pid : components[ind]){
                    m.poly_data(pid).label = searched_label;
                }
            }

            components.clear();
        }
    }

    /*
    m.poly_data(27106).label = 2;
    verts = m.num_verts();
    for(uint vid = 0; vid < verts ; ++vid){
        if( !m.vert_is_manifold_cluster(vid)){
            //Push sphere to GUI
            DrawableSphere sphere(m.vert(vid));
            points.push_back(sphere);
        }
    }
    */

    verts = m.num_verts();
    for(uint vid = 0; vid < verts ; ++vid){
        if( !m.vert_is_manifold_cluster(vid)){

            //Push sphere to GUI
            DrawableSphere sphere(m.vert(vid));
            points.push_back(sphere);
        }
    }

    m.poly_color_wrt_label();
    m.updateGL();


    GLcanvas gui;

    // Push mesh before
    gui.push_obj(&m);

    std::cout << "\nTotal:\nNon Manifold Points: " + to_string(points.size()) << std::endl;
    // Then push other things!  ORDER MATTERS
    for(uint i = 0; i < points.size() ; ++i){
        points[i].size = 0.10;
        points[i].color = Color(1,0,0,0.5);
        gui.push_obj(&points[i]);
   }

    gui.show();

    switch(object) {
      case 1:
        gui.set_scene_center(m.vert(5853), 0.2, true); //Bunny Zoom
        break;
      case 2:
        gui.set_scene_center(m.vert(8468), 0.2, true); //CUP Zoom
        break;
      case 3:
        break;
      default:
        break;
    }
    gui.updateGL();

    // CMD+1 to show mesh controls.
    SurfaceMeshControlPanel<DrawableTrimesh<>> panel(&m, &gui);

    QApplication::connect(new QShortcut(QKeySequence(Qt::CTRL+Qt::Key_1), &gui), &QShortcut::activated, [&](){panel.show();});

    return a.exec();
}
