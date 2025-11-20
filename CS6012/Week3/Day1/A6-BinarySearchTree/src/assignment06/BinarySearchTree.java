package assignment06;

import java.util.ArrayList;
import java.util.Collection;
import java.util.NoSuchElementException;

public class BinarySearchTree<T extends Comparable<? super T>> implements SortedSet<T>{

    public class Node{
        T value = null;
        Node left = null;
        Node right = null;
        public Node(T value){
            this.value = value;
        }
        public Node(T value, Node left, Node right){
            this.value = value;
            this.left = left;
            this.right = right;
        }
    }

    Node root;
    int size;

    public BinarySearchTree(){
        root = null;
        size = 0;
    }

    /**
     * Ensure item is present in tree. Checks if item is present and, if not, places it in order.
     * Recursive driver
     *
     * @param item
     * @return true if set changed
     * @throws NullPointerException
     */
    @Override
    public boolean add(T item) throws NullPointerException{
        if(item == null)
            throw new NullPointerException();

        int startSize = size;
        root = addRec(root, item);

        return startSize != size;
    }

    /**
     * Adds node recursively starting at subroot n. Does nothing if it
     * finds a duplicate
     *
     * @param n
     * @param value
     * @return new root of subtree rooted at n after adding.
     */
    Node addRec(Node n, T value){
        if(n == null) {
            size++;
            return new Node(value);
        }

        int compare =  value.compareTo(n.value);
        if(compare == 0) //if match, change nothing
            return n;
        else if(compare < 0)
            n.left = addRec(n.left, value);
        else
            n.right = addRec(n.right, value);
        return n;
    }

    /**
     * Adds items in collection
     *
     * @param items
     * @return true if anything added, else false
     * @throws NullPointerException
     */
    @Override
    public boolean addAll(Collection<? extends T> items) throws NullPointerException{
        if(items == null)
            throw new NullPointerException();

        int startSize = size;
        for(T item : items)
            add(item);
        return startSize != size;
    }

    /**
     * Resets to empty tree
     */
    @Override
    public void clear() {
        root = null;
        size = 0;
    }

    /**
     * Determines if set contains equal item
     *
     * @param item
     * @return true if set contains equal item, else false
     * @throws NullPointerException
     */
    @Override
    public boolean contains(T item) throws NullPointerException {
        if(item == null)
            throw new NullPointerException();

        Node current = root;
        while(current != null){
            int compare = item.compareTo(current.value);
            if(compare == 0)
                return true;
            else if(compare < 0)
                current = current.left;
            else
                current = current.right;
        }
        return false;
    }

    /**
     * Determines if set contains all items
     *
     * @param items
     * @return true of all items in set
     * @throws NullPointerException
     */
    @Override
    public boolean containsAll(Collection<? extends T> items) throws NullPointerException {
        if(items == null)
            throw new NullPointerException();

        for(T item : items)
            if(!contains(item))
                return false;
        return true;
    }

    /**
     * Returns 1st element in set.
     *
     * @return first T in order in set. Is also the leftmost branch of the tree.
     * @throws NoSuchElementException
     */
    @Override
    public T first() throws NoSuchElementException {
        if(root == null)
            throw new NoSuchElementException();
        Node leftMostNode = root;
        while(leftMostNode.left != null)
            leftMostNode = leftMostNode.left;
        return leftMostNode.value;
    }

    /**
     * You... you know what this does.
     *
     * @return true if set empty.
     */
    @Override
    public boolean isEmpty() {
        return size == 0;
    }

    /**
     * Returns last element in set.
     *
     * @return last T in order in set. Is also the rightmost branch of the tree.
     * @throws NoSuchElementException
     */
    @Override
    public T last() throws NoSuchElementException {
        if(root == null)
            throw new NoSuchElementException();
        Node rightMostNode = root;
        while(rightMostNode.right != null)
            rightMostNode = rightMostNode.right;
        return rightMostNode.value;
    }

    /**
     * Ensure item NOT present in tree. Checks if item is present and, if so, removes and
     * adjusts the tree to maintain binary search tree property
     * Recursive driver
     * @param item
     * @return
     * @throws NullPointerException
     */
    @Override
    public boolean remove(T item) throws NullPointerException{
        if(item == null)
            throw new NullPointerException();

        int startSize = size;
        root = removeRec(root, item);
        return startSize != size;
    }

    /**
     * Remove value from set recursively. W
     * @param n
     * @param value
     * @return
     */
    public Node removeRec(Node n, T value){
        if(n == null)
            return null;

        int compare = value.compareTo(n.value);
        if(compare == 0)
        {
            if(n.left == null && n.right == null) {  // leaf node
                size--;
                return null;
            }
            else if(n.left != null && n.right != null){ //pull new value from predecessor
                Node predecessor = n.left;
                while(predecessor.right != null)
                    predecessor = predecessor.right;
                n.value = predecessor.value;
                n.left = removeRec(n.left, predecessor.value);
                return n;
            } else { //Only child
                size--;
                if(n.left != null)
                    return n.left;
                else
                    return n.right;
            }
        } else if (compare < 0){
            n.left = removeRec(n.left, value);
            return n;
        } else  {
            n.right = removeRec(n.right, value);
            return n;
        }
    }

    /**
     * Removes items in collection
     *
     * @param items
     * @return true if any items removed from set
     */
    @Override
    public boolean removeAll(Collection<? extends T> items) throws NullPointerException {
        if(items == null)
            throw new NullPointerException();

        int startSize = size;
        for(T item : items)
            removeRec(root, item);
        return startSize != size;
    }

    /**
     * @return # of elements in set
     */
    @Override
    public int size() {
        return size;
    }

    /**
     * @return ordered ArrayList of type T
     */
    @Override
    public ArrayList<T> toArrayList() {
        ArrayList<T> list = new ArrayList<>();
        inOrderFillArrayList(list, root);
        return list;
    }

    /**
     * helper function for toArrayList(). In-order recursive traversal to fill an array.
     * @param list
     * @param node
     */
    void inOrderFillArrayList(ArrayList<T> list, Node node){
        if(node.left != null)
            inOrderFillArrayList(list, node.left);
        list.add(node.value);
        if(node.right != null)
            inOrderFillArrayList(list, node.right);
    }

    /**
     * Helper function for testing. Ugly output because testing.
     * @return String of T.toString() in order separated by 1 or more commas.
     */
    String inOrderToString(){
        if(root == null)
            return "";
        return inOrderToStringRec(root);
    }

    /**
     * Recursive helper function for inOrderToString
     * @param n
     * @return String of T.toString() in order separated by 1 or more commas.
     */
    String inOrderToStringRec(Node n){
        String str = "";
        if(n.left != null)
            str += inOrderToStringRec(n.left) + ", ";
        str += n.value.toString();
        if(n.right != null)
            str += ", " + inOrderToStringRec(n.right);
        return str + ", ";
    }

}
