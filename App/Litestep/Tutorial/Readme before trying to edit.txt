The Litestep tutorial is organized like this:
\css - Includes global stylesheets, used for all langs
\js - Global js
\img - Global images, includes:
	Back.png - the image clicked to go to the previous page
	Beggining.png - the image clicked to go back to the beggining
	Cancel.png - the image clicked to cancel
	Next.png - the image clicked to go to the next page
	Finish.png - the image clicked to finish the tutorial
		(only displayed on last page)
	CodeBG.png - the background displayed for code (div class="code")
	*NOTE* It is reccomended to commit your source images as well (photoshop files,
	gimp files, whatever)
\[Lang] - The folder for a particular language
	Eng - English
	Fr - French
	\html - Tutoial pages in the form of Page[#].html
		**DO NOT** include <head> or <html> tags in these files!
		**NOTE** Creating a div with class="code" is reccomended when adding
		code to the tutorial
	\img - The Images for the specific language.
		Upload the files you used to create the image as well (psd, xcf files)
		This folder can contain any images, and this is where
		you should store the images required for your tutorial.