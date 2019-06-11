package fr.graphics;

import fr.geometrie.*;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.*;
import java.util.ArrayList;
import java.util.Collections;


public class Dessin extends JPanel {

    private ArrayList<Figure> list;
    private Color c;
    private String nomFigure;
    private int x = 0;
    private int y = 0;

    //constructeur
     public Dessin() {
        super();
        super.setBackground(Color.WHITE);
        c = Color.black;
        nomFigure = "Rectangle";
        //liste d'objets figures
        list = new ArrayList<Figure>();



    }



    //redefine the paint Components methods
    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2 =  (Graphics2D) g;
        //display all the figures
        for ( Figure f: list){
            //exceptions case
                f.draw(g2);
        }

    }

    public void setC(Color c) {
        this.c = c;
    }

    public void setNomFigure(String nomFigure) {
        this.nomFigure = nomFigure;
    }


    /**
     * Give the Array List
     * @return list
     */
    public ArrayList<Figure> getList() {
        return list;
    }

    /**
     * Erase the Arraylist in order to have a new sheet
     */
    public void nouveau(){
        list.clear();
        c = Color.black;
        nomFigure = "Rectangle";
        repaint();
    }

    /**
     * Remove the last figure object
     */
    public void removeLast(){
        if (list.size() > 0 ){
            list.remove(list.size()-1);
        }
        repaint();
    }
    /**
     * Remove the last figure object
     */
    public void removeNumber(int number){
        if (number>=0){
            list.remove(number);
        }
        repaint();

    }


    /**
     * Moove up or down figures in the arraylist and change the perspective
     * @param value
     * @param cmd
     */
    public void mooveCalques(int value,String cmd){

            if (cmd.equals("UP")){
                if (value > 0) {
                    Collections.swap(list,value-1,value);
                }

            }else if (cmd.equals("DOWN")){
                if(value < list.size()){
                    Collections.swap(list,value,value+1);
                }

            }

        repaint();
    }

    public void saveDessin(String value){
        int indice;
        FileWriter fw;

        try {
            fw = new FileWriter(value,true);

            for (indice=0; indice< list.size(); indice++)
            {
                System.out.println("MARQUEUR");
                fw.write(String.valueOf(list.get(indice).getOrigine()));
            }

            fw.close();

        }catch (FileNotFoundException e) {
            e.printStackTrace();

        }catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Export the pictures
     * @param name
     */
    public void exportDessin(String name){
        BufferedImage bi = new BufferedImage(this.getSize().width, this.getSize().height, BufferedImage.TYPE_INT_ARGB);
        Graphics2D g = bi.createGraphics();
        this.paint(g);  //this == JComponent
        g.dispose();
        try{
            ImageIO.write(bi,"png",new File(name));
        }catch (Exception e) {}
    }

    public void refreshParseur(ArrayList<Figure> list){
        this.list = list;
        repaint();
    }

}