package fr.graphics;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;

public class Panel extends JPanel {
    private int mRows = 0;
    private int mCols = 0;
    public JPanel mPan;
    private ArrayList<Buttons> Blist;

    /**
     * Constructor for a grid layout with buttons
     * @param buttonText
     * @param rows
     * @param cols
     */
    public Panel(String buttonText[][], int rows, int cols){
        mRows = rows;
        mCols = cols;
        mPan = new JPanel();
        mPan.setLayout(new GridLayout(rows,cols));
        Blist = new ArrayList<Buttons>();
        FillButtonsList(buttonText);


    }

    /**
     * grid layout
     * @param rows
     * @param cols
     */
    public Panel(int rows, int cols){
        mRows = rows;
        mCols = cols;
        mPan = new JPanel();
        mPan.setLayout(new GridLayout(rows,cols));
    }

    public Panel(){
        mPan = new JPanel();
    }

    private void FillButtonsList(String[][] buttonText){

        for (int i = 0; i < buttonText[0].length ; i++ ){
            Buttons But = new Buttons(buttonText[0][i]);

            if (buttonText[1][0].contains("$") ){
                mPan.add(But.mButton);

            }else {
                mPan.add(But.mButton).setBackground(Color.decode(buttonText[1][i]));
            }
            Blist.add(But);

        }


    }


    public int getmRows() {
        return mRows;
    }

    public int getmCols() {
        return mCols;
    }

    public ArrayList<Buttons> getBlist() {
        return Blist;
    }

}
