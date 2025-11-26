package assignment07;

public class BadHashFunctor implements HashFunctor{

    /**
     * Hashes from 1st char
     * @param item
     * @return char value of 1st char
     */
    @Override
    public int hash(String item) {
        return (int)item.charAt(0);
    }
}
