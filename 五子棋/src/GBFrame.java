/*
* 五子棋：
*   实现的功能:创建窗体， 创建面板， 绘制棋盘， 绘制棋子， 鼠标监听器的实现， 检查是否有五个同颜色的棋子相连， 线程记录倒计时， 设置倒计时按钮， 重新开始按钮
* 1.窗体，面板： 可以在主方法中通过实例化进行设置， 棋盘， 棋子可以通过paint(Graphics g)方法来绘制
* 2.鼠标监听器： 在其中实现当鼠标点击时所产生的效果， 如点击倒计时按钮可以设置倒计时时间，点击开始按钮可以重新开始新的游戏，
* 点击棋盘中会获取当前鼠标位置，进行判断然后绘制棋子在棋盘上
* 3.棋子相连： 可以用子方法来实现， 模拟横纵坐标，判断各方向上是否有五个棋子相连，如果有就返回true，否则返回false
* 4.线程记录倒计时： 用类实现runnable，每次循环减少1，并睡眠1s， 如果倒计时为0就结束线程，打印结果
 */
import javax.swing.*;
import java.awt.*;

public class GBFrame extends JFrame {

    public static void main(String[] args) {
        //创建窗体对象
        JFrame frame = new JFrame();
        frame.setTitle("五子棋");
        frame.setSize(600, 600);
        frame.setBackground(Color.GRAY);

        //关闭窗体，结束程序
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        //居中显示
        frame.setLocationRelativeTo(null);

        //创建面板对象
        GBPanel P = new GBPanel();
        //禁止最大化
        frame.setResizable(false);

        //添加面板至窗体
        frame.add(P);

        //显示窗体
        frame.setVisible(true);

    }
}
