//本类记录每一步下棋的位置
public class Reback {
    int x, y;//棋子在棋盘上的坐标
    boolean color;//棋子是黑方的或是白方的
    public Reback(int x, int y, boolean color){
        this.x = x;
        this.y = y;
        this.color = color;
    }
    public Reback(){}
}
