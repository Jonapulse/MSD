import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class GrayscaleImageTest {

    private GrayscaleImage smallSquare;
    private GrayscaleImage smallWide;
    private GrayscaleImage smallWideEven;

    @BeforeEach
    void setUp() {
        smallSquare = new GrayscaleImage(new double[][]{{1,2},{3,4}});
        smallWide = new GrayscaleImage(new double[][]{{1,2,3},{4,5,6}});
        smallWideEven = new GrayscaleImage(new double[][]{{1,2,3,4},{5,6,7,8}});
    }

    @Test
    void testGetPixel(){
        assertEquals(smallSquare.getPixel(0,0), 1);
        assertEquals(smallSquare.getPixel(1,0), 2);
        assertEquals(smallSquare.getPixel(0,1), 3);
        assertEquals(smallSquare.getPixel(1,1), 4);

    }

    @Test
    void testGetPixelBounds()
    {
        boolean caughtException = false;
        try{
            smallSquare.getPixel(-1,0);
        } catch(IllegalArgumentException e){
            caughtException = true;
        }
        assertTrue(caughtException);

        try{
            smallSquare.getPixel(2,0);
        } catch(IllegalArgumentException e){
            caughtException = true;
        }
        assertTrue(caughtException);

        try{
            smallSquare.getPixel(0,-1);
        } catch(IllegalArgumentException e){
            caughtException = true;
        }
        assertTrue(caughtException);

        try{
            smallSquare.getPixel(0,2);
        } catch(IllegalArgumentException e){
            caughtException = true;
        }
        assertTrue(caughtException);
    }


    @Test
    void testEquals() {
        assertEquals(smallSquare, smallSquare);
        var equivalent = new GrayscaleImage(new double[][]{{1,2},{3,4}});
        assertEquals(smallSquare, equivalent);
    }

    @Test
    void testNotEquals() {
        var notEquivalent = new GrayscaleImage(new double[][]{{2,3},{1,4}});
        assertNotEquals(smallSquare, notEquivalent);
    }

    @Test
    void testNotEqualsSize() {
        assertNotEquals(smallSquare, smallWide);
    }

    @Test
    void averageBrightness() {
        assertEquals(smallSquare.averageBrightness(), 2.5, 2.5*.001);
        var bigZero = new GrayscaleImage(new double[1000][1000]);
        assertEquals(bigZero.averageBrightness(), 0);
    }

    @Test
    void normalized() {
        var smallNorm = smallSquare.normalized();
        assertEquals(smallNorm.averageBrightness(), 127, 127*.001);
        var scale = 127/2.5;
        var expectedNorm = new GrayscaleImage(new double[][]{{scale, 2*scale},{3*scale, 4*scale}});
        for(var row = 0; row < 2; row++){
            for(var col = 0; col < 2; col++){
                assertEquals(smallNorm.getPixel(col, row), expectedNorm.getPixel(col, row),
                        expectedNorm.getPixel(col, row)*.001,
                        "pixel at row: " + row + " col: " + col + " incorrect");
            }
        }
    }

    @Test
    void mirrored() {
        var expected = new GrayscaleImage(new double[][]{{2,1},{4,3}});
        assertEquals(smallSquare.mirrored(), expected);

        var expectedUneven = new GrayscaleImage(new double[][]{{3,2,1},{6,5,4}});
        assertEquals(smallWide.mirrored(), expectedUneven);
    }

    @Test
    void cropped() {
        var cropped = smallSquare.cropped(1,1,1,1);
        assertEquals(cropped, new GrayscaleImage(new double[][]{{4}}));

        var croppedUneven = smallWide.cropped(0,1,2,2);
        assertEquals(croppedUneven, new GrayscaleImage(new double[][]{{2,3},{5,6}}));
    }

    @Test
    void croppedTiny(){
        var cropped = smallWide.cropped(1,2,1,1);
        assertEquals(cropped.getPixel(0,0), 6);
    }

    @Test
    void squarified() {
        var squared = smallWide.squarified();
        var expected = new GrayscaleImage(new double[][]{{1,2},{4,5}});
        assertEquals(squared, expected);
    }

    @Test
    void squarifiedEven(){
        var squared = smallWideEven.squarified();
        assertEquals(squared,  new GrayscaleImage(new double[][]{{2,3},{6,7}}));
    }


    @Test
    void testGetPixelThrowsOnNegativeX(){
        assertThrows(IllegalArgumentException.class, () -> { smallSquare.getPixel(-1,0);});
    }
}
