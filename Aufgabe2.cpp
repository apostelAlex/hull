#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <fstream>      // std::ifstream



std::vector<std::array<double, 2> > read_points_from_file(std::string filename){


    std::ifstream points;
    points.open(filename);

    //make voctor of strings for every point is one element
    std::vector<std::string>  pointsAsString;
    int i = 0;
    for (std::string line; std::getline(points, line); ) 
    {
        
        pointsAsString.push_back(line);
        
        i++;
    }

    std::string temp;
    std::array<double, 2> doub;
    std::vector<std::array<double, 2> > output;
    for(int n = 0; n<pointsAsString.size(); n++){
        int loc = pointsAsString[n].find(" ");
        temp = pointsAsString[n].substr(0,loc-1);
 
        doub[0] = std::stod(temp);
        
        temp = pointsAsString[n].substr(loc+1, pointsAsString.size()-1);
        doub[1] = std::stod(temp); 
        output.push_back(doub);
    }
    return output;
}

bool sort_by_y(std::array<double, 2> a, std::array<double, 2> b){

    if(a[1]<b[1]){
        return true;
    }
    else if(a[1]==b[1] && a[0]<b[0]){
        return true;
    }
    else{
        return false;
    }
}

bool sort_by_angle(std::array<double, 2> a, std::array<double, 2> b){

    if(a[0]*b[1]-a[1]*b[0] > 0){
        return true;
    }
    else if(a[0]*b[1]-a[1]*b[0] == 0 && std::abs(a[0])> std::abs(b[0])){
        return true;
    }
    else{
        return false;
    }


}

bool grahamScan(std::array<double, 2> a, std::array<double, 2> b, std::array<double, 2> c){

    double res = (b[0]-a[0])*(c[1]-a[1])-(c[0]-a[0]*(b[0]-a[0]));
    if (res>=0){
        return true;
    }
    else{return false;}

}

void convex_hull(std::vector<std::array<double, 2> >& points){
    //std::vector<std::array<double, 2> > 
    std::sort(points.begin(), points.end(), sort_by_y);
    for(int n=1; n<points.size(); n++){
        points[n][0] -= points[0][0];
        points[n][1] -= points[0][1];
    }
    std::sort(points.begin()+1, points.end(), sort_by_angle);

    for(int n=1; n<points.size(); n++){
        points[n][0] += points[0][0];
        points[n][1] += points[0][1];
    }

    for(int n=0; n+2<points.size(); n++){
        if(grahamScan(points[n], points[n+1], points[n+2]) == false){
            points.erase(points.begin()+n+1);
                //points(0) und (size-1) werden nicht gecheckt?
        }


    }
    read_points_from_file("npoints.txt", points);

}

void read_points_from_file(std::string filename, std::vector<std::array<double, 2> >& points){

    std::ofstream ofs (filename, std::ofstream::out);

    std::vector<std::string> temp;
    
    for(int i=0; i<points.size(); i++){
        std::string stemp ="";
        stemp += std::to_string(points[i][0]);
        stemp += " ";
        stemp += std::to_string(points[i][1]);
        temp.push_back(stemp);
        ofs << stemp << "\n";
    }

    ofs.close();    
}

int main(){
    std::string path;
    std::cout << "File: " << std::endl;
    std::cin >> path;
    
    std::vector <std::array<double, 2> > points = read_points_from_file(path); 
    convex_hull(points);

}