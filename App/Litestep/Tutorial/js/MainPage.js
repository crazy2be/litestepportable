// Global Variables
var PageNumber = 1; //The tutorial page we are on
var MaxPages = 4; //The number of pages in the turorial
var Lang = "Eng"; // The language
var Them = "Default"; //The theme

// Handlers
//window.onerror=handleErr;
function LoadingCode() {
	//document.getElementsByTagName('body')[0]
	//	.style.behavior = 'url(\'..\\css\\WH3.htc\')'
	FirstPage();
	LoadIndex();
	LoadLangs();
	LoadThemes();
	LoadTheme();
}

function LoadIndex() {
	var xmlHttpReq = new ActiveXObject("MSXML2.XMLHTTP.3.0");
	try {
		Path = '..\\Lang\\' + Lang + '\\html\\Index.html';
		xmlHttpReq.open("GET", Path, false);
		xmlHttpReq.send();
		//alert(xmlHttpReq.responseText);
		TutorialSelector.innerHTML = xmlHttpReq.responseText;
	} catch (error) {
		alert('Error occured while attempting to retreive index:\n'
			+ '(' + Path + ')\n'
			+ error.message + '\n');
	}
}

function LoadLangs() {
	var xmlHttpReq = new ActiveXObject("MSXML2.XMLHTTP.3.0");
	try {
		Path = '..\\Lang\\Index.xml';
		xmlHttpReq.open("GET", Path, false);
		xmlHttpReq.send();
		var LangsText = xmlHttpReq.responseText.split('\n');
		var LangCode = '';
		var LangName = '';
		var EndHTML = '';
		for (i = 0; i < LangsText.length; i++) {
			LangName = LangsText[i].substring(
				LangsText[i].indexOf('>')+1,
				LangsText[i].lastIndexOf('<'));
			var CodeIndex = LangsText[i].indexOf('code=')+6;
			LangCode = LangsText[i].substring(
				CodeIndex,
				LangsText[i].substring(
					CodeIndex)
					.indexOf('"')+CodeIndex);
			EndHTML += '<a href="#" onclick="ChangeLang(\'';
			EndHTML += LangCode;
			EndHTML += '\')">';
			EndHTML += LangName;
			EndHTML += '</a><br />';
		}
		LangSelector.innerHTML = EndHTML;
	} catch (error) {
		alert('Error occured while attempting to retreive language list:\n'
			+ '(' + Path + ')\n'
			+ error.message + '\n');
	}
}

function LoadThemes() {
	var xmlHttpReq = new ActiveXObject("MSXML2.XMLHTTP.3.0");
	try {
		Path = '..\\Themes\\Index.xml';
		xmlHttpReq.open("GET", Path, false);
		xmlHttpReq.send();
		var ThemesText = xmlHttpReq.responseText.split('\n');
		var ThemeCode = '';
		var ThemeName = '';
		var EndHTML = '';
		for (i = 0; i < ThemesText.length; i++) {
			ThemeCode = ThemesText[i].substring(
				ThemesText[i].indexOf('>')+1,
				ThemesText[i].lastIndexOf('<'));
			var NameIndex = ThemesText[i].indexOf('name=')+6;
			ThemeName = ThemesText[i].substring(
				NameIndex,
				ThemesText[i].substring(
					NameIndex)
					.indexOf('"')+NameIndex);
			EndHTML += '<a href="#" onclick="ChangeTheme(\'';
			EndHTML += ThemeName;
			EndHTML += '\')">';
			EndHTML += ThemeCode;
			EndHTML += '</a><br />';
		}
		ThemeSelector.innerHTML = EndHTML;
	} catch (error) {
		alert('Error occured while attempting to retreive theme list:\n'
			+ '(' + Path + ')\n'
			+ error.message + '\n');
	}
}

function LoadTheme() {
	//document.getElementsByTagName('body')[0]
	//	.style.behavior = 'url(\'..\\css\\WH3.htc\')'
	//var Stuff = '';
	var CSS = document.getElementsByTagName('link');
	CSS[0].href = '..\\Themes\\' + Them + '\\css\\MainPage.css';
	document.getElementsByTagName('body')[0]
		.style.behavior = 'url(\'..\\css\\WH3.htc\')'
	//Stuff += CSS[0].href;
	//Stuff += '\n';
	var Images = ControlDiv.getElementsByTagName('input');
	for (i = 0; i < Images.length; i++) {
		if (Images[i].src != null) {
			var FileName = Images[i].src.substring(
				Images[i].src.lastIndexOf('/')+1);
			Images[i].src = '..\\Themes\\' + Them + '\\img\\' + FileName;
		}
		//Stuff += Images[i].src;
		//Stuff += '\n';
	}
	//alert(Stuff);
}

function ExitCode() {
	if (confirm("Are you sure you wish to exit?\n"
		+ "This tutorial covers only the basics, and will likely reduce frustration later...\n"
		+ "The tutorial will be run the next time you start litestep.")) {
			window.close();
	}
}

function NextPage() {
	if (PageNumber < MaxPages) {
		PageNumber++;
		GotoTutorialPage();
		if (PageNumber == MaxPages) {
			CancelButton.style.display = "none";
			NextButton.src = '..\\Themes\\' + Them + '\\img\\Finish.png';
		}
	} else if (PageNumber == MaxPages) {
		window.close();
	}
}

function PrevPage() {
	PageNumber--;
	if (PageNumber > 1) {
		GotoTutorialPage();
	} else {
		FirstPage();
	}
	if (PageNumber < MaxPages) {
		CancelButton.style.display = "inline";
		NextButton.src = '..\\Themes\\' + Them + '\\img\\Next.png';
	}
}

function FirstPage() {
	//ToggleTutorialSelector()
	PageNumber=1;
	GotoTutorialPage();
	if (PageNumber < MaxPages) {
		CancelButton.style.display = "inline";
		NextButton.src = '..\\Themes\\' + Them + '\\img\\Next.png';
	}
}

function Page(number) {
	PageNumber = number;
	GotoTutorialPage();
}

function GotoTutorialPage() {
	GotoPage("..\\Lang\\" + Lang + "\\html\\Page" + PageNumber + ".html");
}

function GotoPage(Path) {
	var xmlHttpReq = new ActiveXObject("MSXML2.XMLHTTP.3.0");
	try {
		xmlHttpReq.open("GET", Path, false);
		xmlHttpReq.send();
		//alert(xmlHttpReq.responseText);
		ContentDiv.innerHTML = ParseForCode(xmlHttpReq.responseText);
	} catch (error) {
		alert('Error occured while attempting to retreive page:\n'
			+ '(' + Path + ')\n'
			+ error.message + '\n');
	}
	// Find all the images in the loaded document, and correct their paths.
	var Images = ContentDiv.getElementsByTagName('img');
	for (i = 0; i < Images.length; i++) {
		var Image = Images[i].src;
		var FileName = Image.substring(
			Image.lastIndexOf('/')+1);
		var Path = Image.substring(
			0, Image.lastIndexOf('/'));
		Path = Path.substring(
			0, Path.lastIndexOf('/')+1);
		//alert(Path);
		Images[i].src = Path + 'Lang/'
			+ Lang + '/img/' + FileName;
		//alert(Images[i]);
	}
	/*var Codes = getElementsByClass('Code', ContentDiv, 'Div');
	for (i = 0; i < Codes.length; i++) {
		var Code = Codes[i].innerHTML;
		var LastLineFeed = Code.lastIndexOf('\n');
		for (j = 0; j < LastLineFeed; j = Code.indexOf('\n')) {
			
		}
	}*/
	//alert(xmlHttpReq.responseText);
}

function ChangeLang(LanguageCode) {
	Lang = LanguageCode;
	/*BegginingButton.src = "..\\img\\Beggining.png";
	BackButton.src = "..\\img\\Back.png";
	NextButton.src = "..\\img\\Next.png";
	CancelButton.src = "..\\img\\Cancel.png";*/
	GotoTutorialPage();
}

function ChangeTheme(ThemeName) {
	Them = ThemeName;
	LoadTheme();
}

function ToggleTutorialSelectorFunc() {
	//Toggler = TutorialSelectorDiv.style.display;
	TutorialSelector.style.display = 
		(TutorialSelector.style.display == "none")
			? ("block") : ("none");
	ContentDiv.style.width =
		(ContentDiv.style.width == "581px")
			? ("481px") : ("581px");
	ContentDiv.style.left =
		(ContentDiv.style.left == "10px")
			? ("110px") : ("10px");
	ToggleTutorialSelector.style.left =
		(ToggleTutorialSelector.style.left == "0px")
			? ("100px") : ("0px");
}
/*function handleErr(msg, url, l) {
	alert('SOMETHING WENT WRONG');
	alert('Something whent wrong :(\n'
		+ msg
		+ '\nline: ' + url
		+ '\npage: ' + l);
	return false;
}*/

function ParseForCode(ToParse) {
	EndLines = '';
	Lines = new Array();
	Lines = ToParse.split('\n');
	CodeLinePattern = new RegExp('/<div(\\s+)class="(\\s*)code(\\s*)"(.*?)>/i');
	EndCodeBlock = new RegExp('/<\/div>/i');
	TitleMatch = new RegExp('<title>(.*?)</title>');
	InCodeDiv = false;
	for (i = 0; i < Lines.length; i++) {
		//alert(Lines[i]);
		if (TitleMatch.test(Lines[i])) {
			document.title = Lines[i].substring(
				Lines[i].indexOf(">")+1,
				Lines[i].lastIndexOf("<"));
		} else {
			EndLines += Lines[i];
			EndLines += '\n';
		}
		if (InCodeDiv) {
			if (EndCodeBlock.test(Lines[i])) {
				InCodeDiv = false;
			} else {
				EndLines += '<BR />';
			}
		}
	    if (CodeLinePattern.test(Lines[i])) {
			InCodeDiv = true;
			//alert(Lines[i] + '\nMatched!');
		}
	}
	return EndLines;
}

function getElementsByClass(searchClass,node,tag) {
	var classElements = new Array();
	if ( node == null )
		node = document;
	if ( tag == null )
		tag = '*';
	var els = node.getElementsByTagName(tag);
	var elsLen = els.length;
	var pattern = new RegExp("(^|\\s)"+searchClass+"(\\s|$)");
	for (i = 0, j = 0; i < elsLen; i++) {
		if ( pattern.test(els[i].className) ) {
			classElements[j] = els[i];
			j++;
		}
	}
	return classElements;
}