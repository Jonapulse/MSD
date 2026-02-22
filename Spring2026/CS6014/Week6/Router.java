package msd.benjones;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;

public class Router {

    private HashMap<Router, Integer> distances;
    private String name;
    public Router(String name) {
        this.distances = new HashMap<>();
        this.name = name;
    }

    public void onInit() throws InterruptedException {
        distances =  new HashMap<>();
        for (Router router : Network.getRouters()) {
            distances.put(router, (router == this) ? 0 : Integer.MAX_VALUE);
        }
        HashSet<Neighbor> neighbors = Network.getNeighbors(this);
        for (Neighbor neighbor : neighbors) {
            distances.put(neighbor.router, neighbor.cost);
        }
        for(Neighbor neighbor : neighbors) {
            Network.sendDistanceMessage(new Message(this, neighbor.router, distances));
        }
    }

    public void onDistanceMessage(Message message) throws InterruptedException {
        boolean changed = false;
        int distanceToNeighbor = this.distances.get(message.sender);
        for(Router targetRouter : message.distances.keySet()) {
            int distanceFromNeighbor = message.distances.get(targetRouter);
            int distanceThroughNeighbor = distanceToNeighbor + distanceFromNeighbor;
            if(distanceFromNeighbor < Integer.MAX_VALUE && distanceThroughNeighbor < this.distances.get(targetRouter)) {
                this.distances.put(targetRouter, distanceThroughNeighbor);
                changed = true;
            }
        }
        if(changed) {
            for(Neighbor neighbor : Network.getNeighbors(this)) {
                Network.sendDistanceMessage(new Message(this, neighbor.router, distances));
            }
        }
    }


    public void dumpDistanceTable() {
        System.out.println("router: " + this);
        for(Router r : distances.keySet()){
            System.out.println("\t" + r + "\t" + distances.get(r));
        }
    }

    @Override
    public String toString(){
        return "Router: " + name;
    }
}
