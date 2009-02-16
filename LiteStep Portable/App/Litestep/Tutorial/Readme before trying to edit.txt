The Litestep tutorial is organized like this:
\css - Includes global stylesheets, used for all langs
\js - Global js
\[Lang] - The folder for a particular language
	Eng - English
	Fr - French
	Sp - Spanish
	\html - Tutoial pages in the form of Page[#].html
		**DO NOT** include <head> or <html> tags in these files, with the
		exception of Page0.html, the first loaded page, which should be
		a full HTML file.
		**NOTE** Creating a div with class="code" is reccomended when adding
		code to the tutorial
		**NOTE** Page0.html should contain links to the global stylesheet and
		javascript in the head tag, like this:
			<script type="text/javascript" language="javascript" src="..\..\js\MainPage.js"></script>
			<link href="..\..\css\MainPage.css" rel="stylesheet" type="text/css" media="all" />
	\img - The Images for the specific language.
		Upload the files you used to create the image as well (psd, xcf files)
		Should include the following files, as a minimum:
			Back.png - the image clicked to go to the previous page
			Beggining.png - the image clicked to go back to the beggining
			Cancel.png - the image clicked to cancel
			Next.png - the image clicked to go to the next page
			Finish.png - the image clicked to finish the tutorial
				(only displayed on last page)
		The folder can contain any other images as well, and this is where
		you should store the images required for your tutorial.