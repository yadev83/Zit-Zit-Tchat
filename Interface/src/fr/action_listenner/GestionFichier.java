package fr.action_listenner;

import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Files;

import javax.imageio.ImageIO;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import javax.swing.JTextArea;

import fr.graphics.Dessin;
import fr.graphics.Fenetre;
import fr.graphics.Frame;
import fr.graphics.Text_area;
import fr.parseur.Parseur_launch;
import fr.xmleditor.XmlTextPane;

public class GestionFichier implements ActionListener{



	/**
	 * Open an .xml
	 * @return
	 * @throws IOException
	 */
	public File choixOpenFichier () throws IOException {
			JFileChooser dialogue = new JFileChooser(new File("."));
			File fichier = null;
			
			if (dialogue.showOpenDialog(null) == JFileChooser.APPROVE_OPTION) {
				fichier = dialogue.getSelectedFile();
			}
			
			return fichier;
		}


	/**
	 * Take the file value for a string
	 * @param fichier
	 * @return
	 * @throws IOException
	 */
	public String textFichier (File fichier) throws IOException {
			String texte = "";
			BufferedReader lecteurAvecBuffer = null;
			String ligne;


			try {
				lecteurAvecBuffer = new BufferedReader(new FileReader(fichier));
			}
			catch(FileNotFoundException exc) {
				System.out.println("Error");
			}
			
			while ((ligne = lecteurAvecBuffer.readLine()) != null) {
				texte += ligne;
				texte += '\n';
			}
			
			lecteurAvecBuffer.close();
			
			return texte;
		}


	/**
	 * Open a file and display in Xmleditor component
	 * @param xmlTextPane
	 * @param mDessin
	 * @param mParse
	 * @param mFenetre
	 */
		public void openXMLFile (XmlTextPane xmlTextPane, Dessin mDessin, Parseur_launch mParse, Fenetre mFenetre) {
			try {
				if(!xmlTextPane.getText().equals("")) {
					int valueC  = dialogBox();
					
					if(valueC == 0) {
						registerXMLFile(xmlTextPane,mFenetre);
						
						File openFichier = choixOpenFichier();
						
						if(openFichier != null) {
							String codeText = textFichier(openFichier);
							
							xmlTextPane.setText(codeText);
							mFenetre.setTitle("ValouML < " + openFichier.getName() + " >");
						}
					} else if(valueC == 1) {
						fileOperations(xmlTextPane,mDessin,mParse,mFenetre);

					}
				} else {
					fileOperations(xmlTextPane,mDessin,mParse,mFenetre);
				}
				
			} catch (IOException e1) {
				e1.printStackTrace();
			}
		}

	/**
	 * avoid same code
	 * @param xmlTextPane
	 * @param mDessin
	 * @param mParse
	 * @param mFenetre
	 */
		public void  fileOperations(XmlTextPane xmlTextPane, Dessin mDessin, Parseur_launch mParse, Fenetre mFenetre){

			File openFichier;
			try {
				openFichier = choixOpenFichier();
				String codeText = textFichier(openFichier);

				xmlTextPane.setText(codeText);
				mFenetre.setTitle("ValouML < " + openFichier.getName() + " >");

				mParse = new Parseur_launch(openFichier.getAbsolutePath());
				mDessin.refreshParseur(mParse.par.getList());
			} catch (IOException e) {
				e.printStackTrace();
			}


		}


	/**
	 * save a file
	 * @return
	 * @throws IOException
	 */
	public JFileChooser choixSaveFichier () throws IOException {
			JFileChooser dial = new JFileChooser();
			int retour = dial.showSaveDialog(null);
			
			if (retour == JFileChooser.APPROVE_OPTION) {
				//name and absolute path
				dial.getSelectedFile().getName();
				dial.getSelectedFile().getAbsolutePath();
			} else {
				dial = null;
			}
			
			return dial;
		}


	/**
	 * save the xml file
	 * @param xmlTextPane
	 * @param mFenetre
	 */
		public void registerXMLFile (XmlTextPane xmlTextPane, Fenetre mFenetre) {
			try {
				if(!xmlTextPane.getText().equals("")) {
					JFileChooser saveFichier = choixSaveFichier();
					
					if(saveFichier != null) {
						String text = xmlTextPane.getText();
						
						try (FileOutputStream fos = new FileOutputStream(saveFichier.getSelectedFile().getAbsolutePath() + ".isvg")) {
							fos.write(text.getBytes());
						} catch(IOException ex) {
							ex.printStackTrace();
						}
						
						if(mFenetre != null) {
							mFenetre.setTitle("ValouML < " + saveFichier.getSelectedFile().getAbsolutePath() + " >");
						} else {
							mFenetre.setTitle("ValouMl < No Name >");
						}
					}
				}
			} catch (IOException e1) {
				e1.printStackTrace();
			}
		}

	/**
	 * return 0 yes , 1 no , 2 cancel Confirmation box
	 * @return
	 */
	public int dialogBox () {

		int valueConf = JOptionPane.showConfirmDialog(null,"Enregistrer le fichier ?","Options",JOptionPane.YES_NO_CANCEL_OPTION,JOptionPane.QUESTION_MESSAGE);
		return valueConf;
	}

	/**
	 * create a new file
	 * @param xmlTextPane
	 * @param mDessin
	 * @param mFenetre
	 */
		public void newFile (XmlTextPane xmlTextPane, Dessin mDessin, Fenetre mFenetre) {
			if(!xmlTextPane.getText().equals("")) {
				int valueC;
				valueC = dialogBox();
				
				if(valueC == 0) {
					registerXMLFile(xmlTextPane,null);
					xmlTextPane.setText("");
					mDessin.nouveau();
					mFenetre.setTitle("ValouML < No Name >");
				} else if(valueC == 1) {
					xmlTextPane.setText("");
					mDessin.nouveau();
					mFenetre.setTitle("ValouML < No Name >");
				}
			}
		}


	/**
	 * Shut down the file properly
	 * @param xmlTextPane
	 */
	public void quitFile (XmlTextPane xmlTextPane) {
			if(!xmlTextPane.getText().equals("")) {
				int valueC;
				valueC = dialogBox();
				if(valueC == 0) {
					registerXMLFile(xmlTextPane,null);
					System.exit(0);
				} else if(valueC == 1) {
					System.exit(0);
				}
			} else {
				System.exit(0);
			}
		}


	/**
	 * Export the dessin pane
	 * @param mDessin
	 */
	public void exportDessin(Dessin mDessin) {
			try {
				if(mDessin.getList().isEmpty() ) {
					JFileChooser choice= choixSaveFichier();
					if(choice != null) {
						BufferedImage bi = new BufferedImage(mDessin.getSize().width, mDessin.getSize().height, BufferedImage.TYPE_INT_ARGB);
						Graphics g = bi.createGraphics();
						mDessin.paint(g);
						g.dispose();
						
						try{
						    ImageIO.write(bi,"png",new File(choice.getSelectedFile().getAbsolutePath()+".png"));
						} catch (Exception e) {}
					}
				}
				
			} catch (IOException e1) {
				e1.printStackTrace();
			}
		}


		@Override
		public void actionPerformed(ActionEvent e) {
			
		}
		
}
