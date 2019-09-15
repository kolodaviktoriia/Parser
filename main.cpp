#define CURLPP_STATICLIB
#include <iostream>
#include <string>
#include <sstream>
#include <libxml/tree.h>
#include <libxml/HTMLparser.h>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

using namespace std;

void RequestToServer(string link, string &answer) {
	string url = "http://";
	url.append(link);
	curlpp::Cleanup cleanup;
	curlpp::Easy request;
	request.setOpt<curlpp::options::Url>(url);
	ostringstream stream_for_answer;
	curlpp::options::WriteStream stream_writer(&stream_for_answer);
	request.setOpt(stream_writer);
	request.perform();
	answer.append(stream_for_answer.str());
}
void CreateDomFromHtml(string filename, string &html) {
	xmlDoc* dom_tree = htmlReadDoc((xmlChar*)html.c_str(), NULL, NULL, HTML_PARSE_RECOVER | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);
	if (xmlSaveFormatFileEnc(filename.c_str(), dom_tree, "UTF-8", 1) == -1) {
		cout << "File wasn't created" << endl;;
	}
	else {
		cout << "File was created." << endl;
	}
	xmlFreeDoc(dom_tree);
}
int main(int, char**)
{
	string link;
	cout << "Please enter a link to page (e.g. www.google.com/):" << endl;
	cin >> link;
	string html;
	RequestToServer(link,html);
	string filename;
	cout << "Please enter a filename where you will save your dom (e.g. dom.xml):" << endl;
	cin >> filename;
	CreateDomFromHtml(filename,html);
	return 0;
}