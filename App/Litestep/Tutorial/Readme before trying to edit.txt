The Litestep tutorial is organized like this:
\css - Includes global stylesheets, used for all themes
	MainPage.css - All the global styles go in here.
\js - Global js
	MainPage.js - Contains all the js atm.
\html - The "main" html files are in here.
	MainPage.html - The main html page, contains the basic layout.
	Tutorial.hta - The hta that is launched via tutorial.exe, this just loads
	MainPage.html (you can right-click > edit to see for yourself)
\Themes - Contains all the tutorial themes
	Index.xml - Contains the list of installed themes.
	[Theme Name]
		\css - contains the css for the theme.
			MainPage.css - All the css for the theme is in here atm.
		\img - Global images, includes:
			Back.png - the image clicked to go to the previous page
			Beggining.png - the image clicked to go back to the beggining
			Cancel.png - the image clicked to cancel
			Next.png - the image clicked to go to the next page
			Finish.png - the image clicked to finish the tutorial
				(only displayed on last page)
			CodeBG.png - the background displayed for code (div class="code")
			*NOTE* It is reccomended to commit your source images as well
			(photoshop files, gimp files, whatever)
\Lang - This folder contains all the turoial content
	Index.xml - The list of installed languages
	[Lang] - The folder for a particular language, name should be the international
	language code used for that language (e.g. Eng = english, Fr = french, etc.)
		Index.xml - The list of installed tutorials for this language
		[Tutorial Name] - Contains the files for that particular tutorial
			\html - Tutoial pages in the form of Page[#].html
				**DO NOT** include <head> or <html> tags in these files!
				**NOTE** Creating a div with class="code" is reccomended when adding
				code to the tutorial
			\img - The Images for the tutorial.
				Upload the files you used to create the image as well (psd, xcf files)
				This folder can contain any images, and this is where
				you should store the images required for your tutorial.