import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.Stack;


public class GBPanel extends JPanel implements MouseListener, Runnable {
//    BufferedImage bg = null;//背景图片

    int x = 0, y = 0;//存横，纵坐标
    final int n = 16;//常量给数组开空间
    String str = "菜单栏";
    int BTime = 0, WTime = 0, Time = 0;//黑棋倒计时， 白棋倒计时， 设置时间
    int tot;//已下棋子数目
    boolean flag = true;//真表示黑棋 假表示白棋
    boolean put = true;//真表示能放棋子(表示游戏开始运行) 假表示不能放棋子
    String prompt = "黑棋先行";
    String Bprompt = "无限制", Wprompt = "无限制";
    int[][] chess = new int[n][n];//表示棋盘中棋子的状态 0为空位置， 1为黑棋， 2为白棋， 3为悔棋状态
    Stack<Reback> re = new Stack<Reback>();//记录棋子位置的栈

    //无参构造
    public GBPanel(){
//        try {
//            bg = ImageIO.read(new File("D:/j/工程/五子棋/img/bg02.jpg"));
//        } catch (IOException e) {
//            e.printStackTrace();
//        }

        setBackground(Color.lightGray);//设置背景色
        this.addMouseListener(this);//添加鼠标适配器
    }


    //重写MouseListener中的方法
    @Override
    public void mouseClicked(MouseEvent e) {
        // TODO 自动生成的方法存根
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        // TODO 自动生成的方法存根

    }

    @Override
    public void mouseEntered(MouseEvent e) {
        // TODO 自动生成的方法存根

    }

    @Override
    public void mouseExited(MouseEvent e) {
        // TODO 自动生成的方法存根

    }

    @Override
    public void mousePressed(MouseEvent e) {
        //如果此时可以放棋子 就获取棋子的位置
//        如果此时在游戏中，可以放棋子
        if(put) {
            //获取鼠标位置
            x = e.getX();
            y = e.getY();

            //下棋功能
            if(x >= 10 && x <= 370 && y >= 50 && y <= 410) {
                //模糊判断棋子落子的位置大约为以当前坐标为原点，向四周延升边长为一个格子长度的二分之一
                if((x - 10) % 24 > 12) x = (x - 10) / 24 + 1;
                else x = (x - 10) / 24;
                if((y - 50) % 24 > 12) y = (y - 50) / 24 + 1;
                else y = (y - 50) / 24;

                //如果当前位置没有下过
                if(chess[x][y] == 0) {
                    //flag真 为黑棋，将其状态chess[x][y]置为1，下一次是白棋 flag置反，更新信息
                    if(flag) {
                        chess[x][y] = 1;
                        flag = false;
                        prompt = "轮到白方";
                    }
                    else {
                        chess[x][y] = 2;
                        flag = true;
                        prompt = "轮到黑方";
                    }
                    re.push(new Reback(x, y, flag));//记录每次下棋的位置

                    //check()判断输赢，以当前点为基准判断其相连是否有五个
                    if(check()) {
                        int t = chess[x][y];
                        JOptionPane.showMessageDialog(this, "游戏结束" + (t == 1?"黑方":"白方")+"获胜！");
                        put = false;
                        prompt = (t == 1? "黑方" : "白方") + "获胜!";
                    }
                    //如果棋子大于了棋盘总格子数并且没有人胜出，就是平局
                    if(tot >= 255) JOptionPane.showMessageDialog(this, "游戏结束， 本局平局");
                    tot ++;
                }
            }
            this.repaint();
        }


        //开始游戏按钮
        if(e.getX() >= 430 && e.getX() <= 550 && e.getY() >= 45 && e.getY() <= 70){
            //JOptionPane.showConfirDialog如果返回0表示选择为'是'
            int t = JOptionPane.showConfirmDialog(this, "是否开始游戏？");
            if(t == 0) {
                Init();//使用初始化函数开始游戏
            }
            this.repaint();
        }

        //设置时间按钮
        if(e.getX() >= 430 && e.getX() <= 550 && e.getY() >= 90 && e.getY() <= 115){
            String input = JOptionPane.showInputDialog("请输入最大游戏时间(分钟), 0为无限制");
            try {
                Time = Integer.parseInt(input) * 60;//求总秒数
                int result = JOptionPane.showConfirmDialog(this, "设置完成，是否重新开始游戏？");
                if(result == 0 && Time >= 0) {//如果确定重新开始游戏并且时间合法，就调用初始化函数开始游戏
                    Init();
                }
            }catch(NumberFormatException o) {
                JOptionPane.showMessageDialog(this, "请输入正确信息！");
            }
            this.repaint();
        }

        //悔棋按钮
        if(e.getX() >= 430 && e.getX() <= 550 && e.getY() >= 135 && e.getY() <= 160){
            int t = JOptionPane.showConfirmDialog(this, "是否悔棋？");
            //如果确认悔棋， 并且当前在游戏运行时， 并且棋子记录的栈中有元素 进行操作
            if(t == 0 && put && !re.empty()) {
                chess[re.peek().x][re.peek().y] = 3;//设置为悔棋状态
                prompt = !re.peek().color ? "轮到黑方" : "轮到白方";//更新信息
                flag = !re.peek().color;//更新颜色

                re.pop();//悔棋后这个棋子就不能在栈中， 需要弹出它
            }else JOptionPane.showMessageDialog(this, "悔棋失败！");
            this.repaint();
        }
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);//调用父类的paint()函数 将页面重置一下 去除多余的图像内容

        //画背景图
//        g.drawImage(图片,横坐标,纵坐标,null)
//        g.drawImage(bg, 0, 0, 600, 600, null);

        //菜单文字
        g.setFont(new Font("宋体", Font.BOLD, 20));//设置字体格式
        g.setColor(Color.BLACK);//设置字体颜色
        g.drawString(str, 430, 20);

        //开始游戏功能文字
        g.drawRoundRect(430, 45, 120, 25, 30, 30);
        g.drawString("1、开始游戏", 430, 65);

        //设置时间功能文字
        g.drawRoundRect(430, 90, 120, 25, 25, 25);
        g.drawString("2、设置时间", 430, 110);

        //悔棋功能文字
        g.drawRoundRect(430, 135, 120, 25, 25, 25);
        g.drawString("3、悔  棋", 430, 155);

        //绘制信息的文字
        g.drawString("黑棋时间: " + Bprompt, 10, 480);
        g.drawString("白棋时间: " + Wprompt, 10, 500);
        g.drawString("系统信息:" + prompt, 100, 20);


        //画棋盘（棋盘大小15*15, x : 10 ~ 370   y : 50 ~ 410， 24为棋盘一格的距离）
        for (int i = 0; i < n; i++) {
            g.drawLine(10, 50 + i * 24, 370, 50 + i * 24);//棋盘竖线
            g.drawLine(10 + i * 24, 50, 10 + i * 24, 410);//棋盘横线
        }

        //棋子：以10，50为起点，x和y为24(两点间距离)的整数倍  每个点(x,y)表示棋子
        for (int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++)
            {
                int x = i * 24 + 10;
                int y = j * 24 + 50;
                //为1是黑棋,调用fillOval方法画棋子， 为2是白棋， 为3是悔棋
                if(chess[i][j] == 1) {
                    g.setColor(Color.BLACK);
                    g.fillOval(x - 7, y - 7, 14, 14);
                    g.setColor(Color.GRAY);
                    g.drawOval(x - 7, y - 7, 14, 14);//灰色边框, 方便区分
                }
                if (chess[i][j] == 2) {
                    g.setColor(Color.WHITE);
                    g.fillOval(x - 7, y - 7, 14, 14);
                    g.setColor(Color.BLACK);
                    g.drawOval(x - 7, y - 7, 14, 14);//黑色边框，更易区分
                }
                if(chess[i][j] == 3){
                    g.setColor(Color.lightGray);
                    g.fillOval(x - 7, y - 7, 14, 14);//将上次操作的棋子位置用画圆操作，颜色为背景底色

                    g.setColor(Color.BLACK);
                    g.drawLine(x, y - 7, x, y + 7);
                    g.drawLine(x - 7, y, x + 7, y);//画圆后会覆盖掉横线竖线， 这里再重新画上
                    chess[i][j] = 0;//悔棋后本位置就能重新放棋子， 所以置为0
                    tot --;//悔棋 已下棋子计数-1
                }
            }
        }
    }

    //初始化函数
    public void Init(){
        chess = new int[n][n];//重开新棋盘
        flag = put = true;//初始化标记
        BTime = WTime = Time;//初始化倒计时
        prompt = "黑棋先行";
        if(Time > 0) {
            //时：Time / 3600  分： (Time - (时) * 3600 ) / 60  秒： Time - （分 * 60） / 60
            //化简后:
            Wprompt = Bprompt = Time / 3600 + ":" + (Time / 60 - Time / 3600 * 60) + ":" + (Time - Time / 60 * 60);
            Thread t = new Thread(this);
            t.start();
        }else {
            Wprompt = Bprompt = "无限制";
        }
        re.clear();//清空存储棋子记录的栈
    }

//  检查此点各方向相连棋子是否达到5个
    public boolean check() {
        int color = chess[x][y];
        if(checkCount(1,0, color) || checkCount(0,1, color)//调用子方法对各个方向搜索
        || checkCount(1,1, color) || checkCount(1,-1, color))
            return true;
        return false;
    }

    //check子方法的实现
    private boolean checkCount(int x1, int y1, int color) {
        int count = 1;//记录相连棋子的数量，因为从当前棋子开始所以初始值为1
        int t1 = x1;
        int t2 = y1;
        //t1: 横坐标， t2: 纵坐标  横固定，就是判断向上 下方向， 纵固定，就是判断左 右方向， 两都为正， 判断第一象限， 一正一负判断 第三象限
        //下方while同理原理相同，求本次while未能求到的范围
        while (x + t1 >= 0 && x + t1 <= 14 && y + t2 >= 0 && y + t2 <= 14 && color == chess[x + t1][y + t2]) {
            if (t1 != 0) t1 ++;
            if (t2 != 0) {
                if (t2 > 0) t2++;
                else t2 --;
            }
            count ++;//有满足条件的就计数
        }
        t1 = x1;
        t2 = y1;
        while (x - t1 >= 0 && x - t1 <= 14 && y - t2 >= 0 && y - t2 <= 14 && color == chess[x - t1][y - t2]) {
            if (t1 != 0) t1 ++;
            if (t2 != 0) {
                if (t2 > 0) t2 ++;
                else t2 --;
            }
            count ++;
        }
        if(count >= 5) return true;
        return false;
    }

    //倒计时进程
    @Override
    public void run() {
            //只要当前游戏在运行时就进入线程  并且有时间限制
            while(put && Time > 0) {
                //若棋子为黑 对其进行计数  反之
                if(flag) {
                    if(BTime -- == 0) {
                        JOptionPane.showMessageDialog(this, "黑方超时，游戏结束");
                        put = false;
                    }
                }else {
                    if(WTime -- == 0) {
                        JOptionPane.showMessageDialog(this, "白方超时，游戏结束");
                        put = false;
                    }
                }
                //延时1s  捕获异常
                try {
                    Thread.sleep(1000);
                }catch (Exception e) {
                    e.printStackTrace();
                }

                if(Time == 0) Bprompt = Wprompt = "无限制";
                //记录信息
                else {
                    Bprompt = BTime / 3600 + ":" + (BTime / 60 - BTime / 3600 * 60) + ":" + (BTime - BTime / 60 * 60);
                    Wprompt = WTime / 3600 + ":" + (WTime / 60 - WTime / 3600 * 60) + ":" + (WTime - WTime / 60 * 60);
                }
                this.repaint();
            }
    }
}
