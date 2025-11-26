package assignment07;

public class MediocreHashFunctor implements HashFunctor{

    /**
     * Hashes from all chars
     * @param item
     * @return char value of 1st char
     */
    @Override
    public int hash(String item) {
        int hashValue = 0;
        for(int i = 0; i < item.length(); i++){
            hashValue += (int)item.charAt(i);
        }
        return hashValue;
    }
}
