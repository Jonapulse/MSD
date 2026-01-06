package assignment07;

public class GoodHashFunctor implements HashFunctor{

    private final int FNV_PRIME = 0x01000193;
    private final int FNV_OFFSET_BASIS = 0x811c9dc5;
    /**
     * FNV-1a (Fowler-Noll-Vo hash)
     * @param item
     * @return char value of 1st char
     */
    @Override
    public int hash(String item) {
        int hash = FNV_OFFSET_BASIS;
        for(int i = 0; i < item.length(); i++){
            hash = hash ^ item.charAt(i);
            hash = hash * FNV_PRIME;
        }
        return hash;
    }
}
