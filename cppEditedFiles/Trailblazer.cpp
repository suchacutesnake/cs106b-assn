
#include "Trailblazer.h"
#include "queue.h"
#include "priorityqueue.h"
using namespace std;

static const double SUFFICIENT_DIFFERENCE = 0.2;

Path breadthFirstSearch(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    Vector<RoadNode*> path;
    path += start;
    Queue<Vector<RoadNode*>> q;
    q.enqueue(path);
    Set<RoadNode*> vst, nei;//visited, neighbor
    while(!q.isEmpty() && !vst.contains(end)) {
        path = q.dequeue();
        RoadNode* v = path[path.size() - 1];
        v->setColor(Color::GREEN);
        vst.add(v);
        if(v==end) {
            break;
        }
        nei = graph.neighborsOf(v);
        while(!nei.isEmpty()) {
            Vector<RoadNode*> npath(path);
            npath += nei.first();
            if(!vst.contains(nei.first()))
                nei.first()->setColor(Color::YELLOW);
            nei.remove(nei.first());
            q.enqueue(npath);
        }
    }
    return path;
}

Path dijkstrasAlgorithm(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    double cost = 0;
    Vector<RoadNode*> path;
    path += start;
    PriorityQueue<Vector<RoadNode*>> q;
    q.enqueue(path, cost);
    Set<RoadNode*> vst, nei;
    while(!q.isEmpty() && !vst.contains(end)) {
        cost = q.peekPriority();
        path = q.dequeue();
        RoadNode* v = path[path.size() - 1];
        v->setColor(Color::GREEN);
        vst.add(v);
        if(v==end) {
            break;
        }
        nei = graph.neighborsOf(v);
        while(!nei.isEmpty()) {
            Vector<RoadNode*> npath(path);//newPath
            npath += nei.first();
            if(!vst.contains(nei.first()))
                nei.first()->setColor(Color::YELLOW);
            RoadEdge* edge = graph.edgeBetween(v, nei.first());
            double temp = edge->cost();
            cost += temp;
            nei.remove(nei.first());
            q.enqueue(npath, cost);
            cost -= temp;
        }
    }
    return path;
}

Path aStar(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    double cost = 0;
    Vector<RoadNode*> path;
    path += start;
    PriorityQueue<Vector<RoadNode*>> q;
    q.enqueue(path, cost);
    Set<RoadNode*> vst, nei;
    while(!q.isEmpty() && !vst.contains(end)) {
        double currCost = q.peekPriority();
        path = q.dequeue();
        RoadNode* v = path[path.size() - 1];
        //for now, currCost = realCost + heuristicResult, what we want is the realCost
        //so minus the heuristicResult
        currCost -= graph.crowFlyDistanceBetween(v, end)/graph.maxRoadSpeed();
        v->setColor(Color::GREEN);
        vst.add(v);
        if(v==end) {
            break;
        }
        nei = graph.neighborsOf(v);
        while(!nei.isEmpty()) {
            cost = currCost;
            Vector<RoadNode*> npath(path);//newPath
            npath += nei.first();
            if(!vst.contains(nei.first()))
                nei.first()->setColor(Color::YELLOW);
            RoadEdge* edge = graph.edgeBetween(v, nei.first());
            cost += edge->cost();
            cost += graph.crowFlyDistanceBetween(nei.first(), end)/graph.maxRoadSpeed();
            nei.remove(nei.first());
            q.enqueue(npath, cost);
        }
    }
    return path;
}

Path alternativeRoute(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    Vector<RoadNode*> path, difPath;
    //the PriorityQueue is to select the shortest alternative
    //that also has a difference greater that 0.2
    PriorityQueue<Vector<RoadNode*>> pq;
    //find the shortest path
    path = aStar(graph, start, end);
    //store all the nodes in the shortest path so that
    //I can distinguish nodes in path that are not in difPath later
    Set<RoadNode*> pathNodeSet;
    for(int i = 0; i < path.size(); i++) {
        pathNodeSet.add(path[i]);
    }
    //find alternative path
    for(int i=0;i<path.size()-1;i++) {
        double cost = 0;
        difPath += start;
        PriorityQueue<Vector<RoadNode*>> q;
        q.enqueue(difPath, cost);
        Set<RoadNode*> vst, nei;
        while(!q.isEmpty() && !vst.contains(end)) {
            double currCost = q.peekPriority();
            difPath = q.dequeue();
            RoadNode* v = difPath[difPath.size() - 1];
            currCost -= graph.crowFlyDistanceBetween(v, end)/graph.maxRoadSpeed();
            v->setColor(Color::GREEN);
            vst.add(v);
            if(v==end) {
                break;
            }
            nei = graph.neighborsOf(v);
            while(!nei.isEmpty()) {
                cost = currCost;
                Vector<RoadNode*> npath(difPath);//newPath
                npath += nei.first();
                if(!vst.contains(nei.first()))
                    nei.first()->setColor(Color::YELLOW);
                //ignore the specific edge
                if(path[i]->nodeName()==v->nodeName() &&
                        path[i+1]->nodeName()==nei.first()->nodeName()) {
                    nei.remove(nei.first());
                    continue;
                }
                RoadEdge* edge = graph.edgeBetween(v, nei.first());
                cost += edge->cost();
                cost += graph.crowFlyDistanceBetween(nei.first(), end)/graph.maxRoadSpeed();
                nei.remove(nei.first());
                q.enqueue(npath, cost);
            }
        }
        //compare the nodes in path and difPath
        double dif = 0;
        for(int i=0;i<difPath.size();i++){
            //debug
            string ss=difPath[i]->nodeName();
            //
            if(!pathNodeSet.contains(difPath[i])){
                dif++;
            }
        }
        double difScore = dif/difPath.size();
        if(difScore>SUFFICIENT_DIFFERENCE){
            pq.enqueue(difPath, difScore);
            difPath.clear();
        } else {
            difPath.clear();
        }
    }
    return pq.peek();
}
