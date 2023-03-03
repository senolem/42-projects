/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Header.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melones <melones@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:30:22 by melones           #+#    #+#             */
/*   Updated: 2023/03/03 14:06:17 by melones          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header.hpp"

Header::Header(webserv &webserv_, std::multimap<std::string, t_route> &vhosts) : _webserv(webserv_), _vhosts(vhosts)
{
	initTypes();
	initErrors();
}

Header::Header(const Header &src) : _webserv(src._webserv), _vhosts(src._vhosts), _typesMap(src._typesMap), _errorsMap(src._errorsMap)
{

}

Header::~Header(void)
{

}

Header	&Header::operator=(const Header &src)
{
	if (this != &src)
	{
		this->_webserv = src._webserv;
		this->_vhosts = src._vhosts;
		this->_typesMap = src._typesMap;
		this->_errorsMap = src._errorsMap;
	}
	return (*this);
}

t_request_header	Header::parseRequest(std::string buffer)
{
	t_request_header									header;
	std::vector<std::string>							bufferVect;
	std::vector<std::string>							vect;
	std::vector<std::string>							vect2;
	vectorIterator										vectIter;
	std::string											method;
	std::string											host;
	std::vector<std::multimap<std::string, t_route> >	&vhosts = _webserv.getVirtualHosts();

	bufferVect = split_string(buffer, "\r\n");
	host = getHeader(bufferVect, "Host:");
	if (host.empty())
	{
		header.status = 400;
		return (header);
	}
	vect = split_string(host, " ");
	if (vect.size() != 2)
	{
		header.status = 400;
		return (header);
	}
	header.host = vect.at(1);
	vect2 = split_string(bufferVect.at(0), " ");
	if (vect2.size() != 3)
	{
		header.status = 400;
		return (header);
	}
	header.method = vect2.at(0);
	if (header.method != "GET" && header.method != "POST" && header.method != "DELETE")
	{
		header.status = 501;
		return (header);
	}
	header.version = vect2.at(2);
	vectIter = _webserv.getHost(header.host);
	if (vectIter != vhosts.end())
		header.path = getPath(vectIter, vect2.at(1));
	else
		header.path = getPath(vhosts.begin(), vect2.at(1));
	if (access(header.path.c_str(), R_OK) != 0)
		header.status = 404;
	return (header);
}

std::string	Header::getResponse(t_request_header request)
{
	std::stringstream	fileStream;
	std::stringstream	responseStream;
	t_response_header	header;
	
	if (request.status != 0)
	{
		header.content_type = "text/html";
		std::map<int, std::string>::iterator	errorIter;
		errorIter = _errorsMap.find(request.status);
		if (errorIter != _errorsMap.end())
			header.status_code = errorIter->second;
		else
			header.status_code = "500 Internal Server Error";
		header.content_length = 0;
		std::map<int, std::string>::iterator	iter;
		iter = _vhosts.begin()->second.error_page.find(request.status);
		if (iter != _vhosts.begin()->second.error_page.end())
		{
			if (access(iter->second.c_str(), R_OK) == 0)
			{
				std::ifstream	file(iter->second.c_str(), std::ios::binary);
				fileStream << file.rdbuf();
				header.content = fileStream.str();
				header.content_length = header.content.size();
			}
		}
	}
	else
	{
		setFiletype(&header, request.path);
		std::ifstream	file(request.path.c_str(), std::ios::binary);
		fileStream << file.rdbuf();
		header.status_code = "200 OK";
		header.content = fileStream.str();
		header.content_length = header.content.size();
	}
	responseStream << header.version << " " << header.status_code << std::endl << "Content-Type: " << header.content_type\
	<< std::endl << "Content-Length: " << header.content_length << std::endl << std::endl << header.content;
	return (responseStream.str());
}

std::string	Header::getPath(vectorIterator vectIter, std::string path)
{
	std::vector<std::string>	vect;
	std::string					search;
	mapIterator					mapIter = vectIter->begin();
	mapIterator					mapIter2 = vectIter->end();
	std::string					result;
	size_t						i = 0;

	if (path != "/")
		vect = split_string(path, "/");
	else
		vect.push_back("/");
	if (path.find_last_of('/') == path.length())
		search = vect.at(0).substr(0, vect.at(0).length() - 1);
	else
		search = vect.at(0);
	while (mapIter != mapIter2)
	{
		if (mapIter->second.type == LOCATION && mapIter->second.match == "/" + search)
		{
			result = mapIter->second.root + path;
			i = result.find("/" + search, 0);
			if (i != std::string::npos)
				result.erase(i, search.length() + 1);
			if (path.find_last_of('.') == std::string::npos)
			{
				for (size_t j = 0; j < mapIter->second.index.size(); j++)
				{
					if (access((result + "/" + mapIter->second.index[j]).c_str(), R_OK) == 0)
						return (result + "/" + mapIter->second.index[j]);
				}
			}
			return (result);
		}
		++mapIter;
	}
	if (path.find_last_of('.') == std::string::npos)
	{
		for (size_t j = 0; j < vectIter->begin()->second.index.size(); j++)
		{
			if (access((vectIter->begin()->second.root + "/" + vectIter->begin()->second.index[j]).c_str(), R_OK) == 0)
				return (vectIter->begin()->second.root + "/" + vectIter->begin()->second.index[j]);
		}
	}
	return (vectIter->begin()->second.root + path);
}

void	Header::setFiletype(t_response_header *header, std::string path)
{
	std::vector<std::string>						vect;
	std::string										filetype;
	std::map<std::string, std::string>::iterator	iter;

	vect = split_string(path, ".");
	if (!vect.empty())
		filetype = vect.at(vect.size() - 1);
	iter = _typesMap.find(filetype);
	if (iter != _typesMap.end())
		header->content_type = iter->second;
	else
		header->content_type = "text/plain";
}

std::string	Header::getHeader(std::vector<std::string> header, std::string field)
{
	size_t								i = 0;
	std::vector<std::string>::iterator	iter = header.begin();
	std::vector<std::string>::iterator	iter2 = header.end();
	std::string							ret;

	while (iter != iter2)
	{
		i = iter->find(field);
		if (i != std::string::npos)
		{
			if (i == 0)
				return (*iter);
			else
				return (ret);
		}
		++iter;
	}
	return (ret);
}

void	Header::initErrors(void)
{
	_errorsMap[400] = "400 Bad Request";
	_errorsMap[401] = "401 Unauthorized";
	_errorsMap[403] = "403 Forbidden";
	_errorsMap[404] = "404 Not Found";
	_errorsMap[405] = "405 Method Not Allowed";
	_errorsMap[406] = "406 Not Acceptable";
	_errorsMap[408] = "408 Request Timeout";
	_errorsMap[409] = "409 Timeout";
	_errorsMap[410] = "410 Gone";
	_errorsMap[411] = "401 Length Required";
	_errorsMap[412] = "412 Precondition Failed";
	_errorsMap[413] = "413 Content Too Large";
	_errorsMap[414] = "414 URI Too Long";
	_errorsMap[415] = "415 Unsupported Media Type";
	_errorsMap[416] = "416 Range Not Satisfiable";
	_errorsMap[417] = "417 Expectation Failed";
	_errorsMap[421] = "421 Misdirected Request";
	_errorsMap[428] = "428 Precondition Required";
	_errorsMap[429] = "429 Too Many Requests";
	_errorsMap[431] = "431 Request Header Fields Too Large";
	_errorsMap[500] = "500 Internal Server Error";
	_errorsMap[501] = "501 Not Implented";
	_errorsMap[502] = "502 Bad Gateway";
	_errorsMap[503] = "503 Service Unavailable";
	_errorsMap[504] = "504 Gateway Timeout";
	_errorsMap[505] = "505 HTTP Version Not Supported";
	_errorsMap[511] = "511 Network Authentication Required";

}

void	Header::initTypes(void)
{
	_typesMap["323"] = "text/h323";
    _typesMap["3g2"] = "video/3gpp2";
    _typesMap["3gp"] = "video/3gpp";
    _typesMap["3gp2"] = "video/3gpp2";
    _typesMap["3gpp"] = "video/3gpp";
    _typesMap["7z"] = "application/x-7z-compressed";
    _typesMap["aa"] = "audio/audible";
    _typesMap["AAC"] = "audio/aac";
    _typesMap["aaf"] = "application/octet-stream";
    _typesMap["aax"] = "audio/vnd.audible.aax";
    _typesMap["ac3"] = "audio/ac3";
    _typesMap["aca"] = "application/octet-stream";
    _typesMap["accda"] = "application/msaccess.addin";
    _typesMap["accdb"] = "application/msaccess";
    _typesMap["accdc"] = "application/msaccess.cab";
    _typesMap["accde"] = "application/msaccess";
    _typesMap["accdr"] = "application/msaccess.runtime";
    _typesMap["accdt"] = "application/msaccess";
    _typesMap["accdw"] = "application/msaccess.webapplication";
    _typesMap["accft"] = "application/msaccess.ftemplate";
    _typesMap["acx"] = "application/internet-property-stream";
    _typesMap["AddIn"] = "text/xml";
    _typesMap["ade"] = "application/msaccess";
    _typesMap["adobebridge"] = "application/x-bridge-url";
    _typesMap["adp"] = "application/msaccess";
    _typesMap["ADT"] = "audio/vnd.dlna.adts";
    _typesMap["ADTS"] = "audio/aac";
    _typesMap["afm"] = "application/octet-stream";
    _typesMap["ai"] = "application/postscript";
    _typesMap["aif"] = "audio/aiff";
    _typesMap["aifc"] = "audio/aiff";
    _typesMap["aiff"] = "audio/aiff";
    _typesMap["air"] = "application/vnd.adobe.air-application-installer-package+zip";
    _typesMap["amc"] = "application/mpeg";
    _typesMap["anx"] = "application/annodex";
    _typesMap["apk"] = "application/vnd.android.package-archive";
    _typesMap["apng"] = "image/apng";
    _typesMap["application"] = "application/x-ms-application";
    _typesMap["art"] = "image/x-jg";
    _typesMap["asa"] = "application/xml";
    _typesMap["asax"] = "application/xml";
    _typesMap["ascx"] = "application/xml";
    _typesMap["asd"] = "application/octet-stream";
    _typesMap["asf"] = "video/x-ms-asf";
    _typesMap["ashx"] = "application/xml";
    _typesMap["asi"] = "application/octet-stream";
    _typesMap["asm"] = "text/plain";
    _typesMap["asmx"] = "application/xml";
    _typesMap["aspx"] = "application/xml";
    _typesMap["asr"] = "video/x-ms-asf";
    _typesMap["asx"] = "video/x-ms-asf";
    _typesMap["atom"] = "application/atom+xml";
    _typesMap["au"] = "audio/basic";
    _typesMap["avci"] = "image/avci";
    _typesMap["avcs"] = "image/avcs";
    _typesMap["avi"] = "video/x-msvideo";
    _typesMap["avif"] = "image/avif";
    _typesMap["avifs"] = "image/avif-sequence";
    _typesMap["axa"] = "audio/annodex";
    _typesMap["axs"] = "application/olescript";
    _typesMap["axv"] = "video/annodex";
    _typesMap["bas"] = "text/plain";
    _typesMap["bcpio"] = "application/x-bcpio";
    _typesMap["bin"] = "application/octet-stream";
    _typesMap["bmp"] = "image/bmp";
    _typesMap["c"] = "text/plain";
    _typesMap["cab"] = "application/octet-stream";
    _typesMap["caf"] = "audio/x-caf";
    _typesMap["calx"] = "application/vnd.ms-office.calx";
    _typesMap["cat"] = "application/vnd.ms-pki.seccat";
    _typesMap["cc"] = "text/plain";
    _typesMap["cd"] = "text/plain";
    _typesMap["cdda"] = "audio/aiff";
    _typesMap["cdf"] = "application/x-cdf";
    _typesMap["cer"] = "application/x-x509-ca-cert";
    _typesMap["cfg"] = "text/plain";
    _typesMap["chm"] = "application/octet-stream";
    _typesMap["class"] = "application/x-java-applet";
    _typesMap["clp"] = "application/x-msclip";
    _typesMap["cmd"] = "text/plain";
    _typesMap["cmx"] = "image/x-cmx";
    _typesMap["cnf"] = "text/plain";
    _typesMap["cod"] = "image/cis-cod";
    _typesMap["config"] = "application/xml";
    _typesMap["contact"] = "text/x-ms-contact";
    _typesMap["coverage"] = "application/xml";
    _typesMap["cpio"] = "application/x-cpio";
    _typesMap["cpp"] = "text/plain";
    _typesMap["crd"] = "application/x-mscardfile";
    _typesMap["crl"] = "application/pkix-crl";
    _typesMap["crt"] = "application/x-x509-ca-cert";
    _typesMap["cs"] = "text/plain";
    _typesMap["csdproj"] = "text/plain";
    _typesMap["csh"] = "application/x-csh";
    _typesMap["csproj"] = "text/plain";
    _typesMap["css"] = "text/css";
    _typesMap["csv"] = "text/csv";
    _typesMap["cur"] = "application/octet-stream";
    _typesMap["czx"] = "application/x-czx";
    _typesMap["cxx"] = "text/plain";
    _typesMap["dat"] = "application/octet-stream";
    _typesMap["datasource"] = "application/xml";
    _typesMap["dbproj"] = "text/plain";
    _typesMap["dcr"] = "application/x-director";
    _typesMap["def"] = "text/plain";
    _typesMap["deploy"] = "application/octet-stream";
    _typesMap["der"] = "application/x-x509-ca-cert";
    _typesMap["dgml"] = "application/xml";
    _typesMap["dib"] = "image/bmp";
    _typesMap["dif"] = "video/x-dv";
    _typesMap["dir"] = "application/x-director";
    _typesMap["disco"] = "text/xml";
    _typesMap["divx"] = "video/divx";
    _typesMap["dll"] = "application/x-msdownload";
    _typesMap["dll.config"] = "text/xml";
    _typesMap["dlm"] = "text/dlm";
    _typesMap["doc"] = "application/msword";
    _typesMap["docm"] = "application/vnd.ms-word.document.macroEnabled.12";
    _typesMap["docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
    _typesMap["dot"] = "application/msword";
    _typesMap["dotm"] = "application/vnd.ms-word.template.macroEnabled.12";
    _typesMap["dotx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.template";
    _typesMap["dsp"] = "application/octet-stream";
    _typesMap["dsw"] = "text/plain";
    _typesMap["dtd"] = "text/xml";
    _typesMap["dtsConfig"] = "text/xml";
    _typesMap["dv"] = "video/x-dv";
    _typesMap["dvi"] = "application/x-dvi";
    _typesMap["dwf"] = "drawing/x-dwf";
    _typesMap["dwg"] = "application/acad";
    _typesMap["dwp"] = "application/octet-stream";
    _typesMap["dxf"] = "application/x-dxf";
    _typesMap["dxr"] = "application/x-director";
    _typesMap["eml"] = "message/rfc822";
    _typesMap["emf"] = "image/emf";
    _typesMap["emz"] = "application/octet-stream";
    _typesMap["eot"] = "application/vnd.ms-fontobject";
    _typesMap["eps"] = "application/postscript";
    _typesMap["es"] = "application/ecmascript";
    _typesMap["etl"] = "application/etl";
    _typesMap["etx"] = "text/x-setext";
    _typesMap["evy"] = "application/envoy";
    _typesMap["exe"] = "application/vnd.microsoft.portable-executable";
    _typesMap["exe.config"] = "text/xml";
    _typesMap["f4v"] = "video/mp4";
    _typesMap["fdf"] = "application/vnd.fdf";
    _typesMap["fif"] = "application/fractals";
    _typesMap["filters"] = "application/xml";
    _typesMap["fla"] = "application/octet-stream";
    _typesMap["flac"] = "audio/flac";
    _typesMap["flr"] = "x-world/x-vrml";
    _typesMap["flv"] = "video/x-flv";
    _typesMap["fsscript"] = "application/fsharp-script";
    _typesMap["fsx"] = "application/fsharp-script";
    _typesMap["generictest"] = "application/xml";
    _typesMap["geojson"] = "application/geo+json";
    _typesMap["gif"] = "image/gif";
    _typesMap["gpx"] = "application/gpx+xml";
    _typesMap["group"] = "text/x-ms-group";
    _typesMap["gsm"] = "audio/x-gsm";
    _typesMap["gtar"] = "application/x-gtar";
    _typesMap["gz"] = "application/x-gzip";
    _typesMap["h"] = "text/plain";
    _typesMap["hdf"] = "application/x-hdf";
    _typesMap["hdml"] = "text/x-hdml";
    _typesMap["heic"] = "image/heic";
    _typesMap["heics"] = "image/heic-sequence";
    _typesMap["heif"] = "image/heif";
    _typesMap["heifs"] = "image/heif-sequence";
    _typesMap["hhc"] = "application/x-oleobject";
    _typesMap["hhk"] = "application/octet-stream";
    _typesMap["hhp"] = "application/octet-stream";
    _typesMap["hlp"] = "application/winhlp";
    _typesMap["hpp"] = "text/plain";
    _typesMap["hqx"] = "application/mac-binhex40";
    _typesMap["hta"] = "application/hta";
    _typesMap["htc"] = "text/x-component";
    _typesMap["htm"] = "text/html";
    _typesMap["html"] = "text/html";
    _typesMap["htt"] = "text/webviewhtml";
    _typesMap["hxa"] = "application/xml";
    _typesMap["hxc"] = "application/xml";
    _typesMap["hxd"] = "application/octet-stream";
    _typesMap["hxe"] = "application/xml";
    _typesMap["hxf"] = "application/xml";
    _typesMap["hxh"] = "application/octet-stream";
    _typesMap["hxi"] = "application/octet-stream";
    _typesMap["hxk"] = "application/xml";
    _typesMap["hxq"] = "application/octet-stream";
    _typesMap["hxr"] = "application/octet-stream";
    _typesMap["hxs"] = "application/octet-stream";
    _typesMap["hxt"] = "text/html";
    _typesMap["hxv"] = "application/xml";
    _typesMap["hxw"] = "application/octet-stream";
    _typesMap["hxx"] = "text/plain";
    _typesMap["i"] = "text/plain";
    _typesMap["ical"] = "text/calendar";
    _typesMap["icalendar"] = "text/calendar";
    _typesMap["ico"] = "image/x-icon";
    _typesMap["ics"] = "text/calendar";
    _typesMap["idl"] = "text/plain";
    _typesMap["ief"] = "image/ief";
    _typesMap["ifb"] = "text/calendar";
    _typesMap["iii"] = "application/x-iphone";
    _typesMap["inc"] = "text/plain";
    _typesMap["inf"] = "application/octet-stream";
    _typesMap["ini"] = "text/plain";
    _typesMap["inl"] = "text/plain";
    _typesMap["ins"] = "application/x-internet-signup";
    _typesMap["ipa"] = "application/x-itunes-ipa";
    _typesMap["ipg"] = "application/x-itunes-ipg";
    _typesMap["ipproj"] = "text/plain";
    _typesMap["ipsw"] = "application/x-itunes-ipsw";
    _typesMap["iqy"] = "text/x-ms-iqy";
    _typesMap["isp"] = "application/x-internet-signup";
    _typesMap["isma"] = "application/octet-stream";
    _typesMap["ismv"] = "application/octet-stream";
    _typesMap["ite"] = "application/x-itunes-ite";
    _typesMap["itlp"] = "application/x-itunes-itlp";
    _typesMap["itms"] = "application/x-itunes-itms";
    _typesMap["itpc"] = "application/x-itunes-itpc";
    _typesMap["IVF"] = "video/x-ivf";
    _typesMap["jar"] = "application/java-archive";
    _typesMap["java"] = "application/octet-stream";
    _typesMap["jck"] = "application/liquidmotion";
    _typesMap["jcz"] = "application/liquidmotion";
    _typesMap["jfif"] = "image/pjpeg";
    _typesMap["jnlp"] = "application/x-java-jnlp-file";
    _typesMap["jpb"] = "application/octet-stream";
    _typesMap["jpe"] = "image/jpeg";
    _typesMap["jpeg"] = "image/jpeg";
    _typesMap["jpg"] = "image/jpeg";
    _typesMap["js"] = "application/javascript";
    _typesMap["json"] = "application/json";
    _typesMap["jsx"] = "text/jscript";
    _typesMap["jsxbin"] = "text/plain";
    _typesMap["key"] = "application/vnd.apple.keynote";
    _typesMap["latex"] = "application/x-latex";
    _typesMap["library-ms"] = "application/windows-library+xml";
    _typesMap["lit"] = "application/x-ms-reader";
    _typesMap["loadtest"] = "application/xml";
    _typesMap["lpk"] = "application/octet-stream";
    _typesMap["lsf"] = "video/x-la-asf";
    _typesMap["lst"] = "text/plain";
    _typesMap["lsx"] = "video/x-la-asf";
    _typesMap["lzh"] = "application/octet-stream";
    _typesMap["m13"] = "application/x-msmediaview";
    _typesMap["m14"] = "application/x-msmediaview";
    _typesMap["m1v"] = "video/mpeg";
    _typesMap["m2t"] = "video/vnd.dlna.mpeg-tts";
    _typesMap["m2ts"] = "video/vnd.dlna.mpeg-tts";
    _typesMap["m2v"] = "video/mpeg";
    _typesMap["m3u"] = "audio/x-mpegurl";
    _typesMap["m3u8"] = "audio/x-mpegurl";
    _typesMap["m4a"] = "audio/m4a";
    _typesMap["m4b"] = "audio/m4b";
    _typesMap["m4p"] = "audio/m4p";
    _typesMap["m4r"] = "audio/x-m4r";
    _typesMap["m4v"] = "video/x-m4v";
    _typesMap["mac"] = "image/x-macpaint";
    _typesMap["mak"] = "text/plain";
    _typesMap["man"] = "application/x-troff-man";
    _typesMap["manifest"] = "application/x-ms-manifest";
    _typesMap["map"] = "text/plain";
    _typesMap["master"] = "application/xml";
    _typesMap["mbox"] = "application/mbox";
    _typesMap["mda"] = "application/msaccess";
    _typesMap["mdb"] = "application/x-msaccess";
    _typesMap["mde"] = "application/msaccess";
    _typesMap["mdp"] = "application/octet-stream";
    _typesMap["me"] = "application/x-troff-me";
    _typesMap["mfp"] = "application/x-shockwave-flash";
    _typesMap["mht"] = "message/rfc822";
    _typesMap["mhtml"] = "message/rfc822";
    _typesMap["mid"] = "audio/mid";
    _typesMap["midi"] = "audio/mid";
    _typesMap["mix"] = "application/octet-stream";
    _typesMap["mk"] = "text/plain";
    _typesMap["mk3d"] = "video/x-matroska-3d";
    _typesMap["mka"] = "audio/x-matroska";
    _typesMap["mkv"] = "video/x-matroska";
    _typesMap["mmf"] = "application/x-smaf";
    _typesMap["mno"] = "text/xml";
    _typesMap["mny"] = "application/x-msmoney";
    _typesMap["mod"] = "video/mpeg";
    _typesMap["mov"] = "video/quicktime";
    _typesMap["movie"] = "video/x-sgi-movie";
    _typesMap["mp2"] = "video/mpeg";
    _typesMap["mp2v"] = "video/mpeg";
    _typesMap["mp3"] = "audio/mpeg";
    _typesMap["mp4"] = "video/mp4";
    _typesMap["mp4v"] = "video/mp4";
    _typesMap["mpa"] = "video/mpeg";
    _typesMap["mpe"] = "video/mpeg";
    _typesMap["mpeg"] = "video/mpeg";
    _typesMap["mpf"] = "application/vnd.ms-mediapackage";
    _typesMap["mpg"] = "video/mpeg";
    _typesMap["mpp"] = "application/vnd.ms-project";
    _typesMap["mpv2"] = "video/mpeg";
    _typesMap["mqv"] = "video/quicktime";
    _typesMap["ms"] = "application/x-troff-ms";
    _typesMap["msg"] = "application/vnd.ms-outlook";
    _typesMap["msi"] = "application/octet-stream";
    _typesMap["mso"] = "application/octet-stream";
    _typesMap["mts"] = "video/vnd.dlna.mpeg-tts";
    _typesMap["mtx"] = "application/xml";
    _typesMap["mvb"] = "application/x-msmediaview";
    _typesMap["mvc"] = "application/x-miva-compiled";
    _typesMap["mxf"] = "application/mxf";
    _typesMap["mxp"] = "application/x-mmxp";
    _typesMap["nc"] = "application/x-netcdf";
    _typesMap["nsc"] = "video/x-ms-asf";
    _typesMap["numbers"] = "application/vnd.apple.numbers";
    _typesMap["nws"] = "message/rfc822";
    _typesMap["ocx"] = "application/octet-stream";
    _typesMap["oda"] = "application/oda";
    _typesMap["odb"] = "application/vnd.oasis.opendocument.database";
    _typesMap["odc"] = "application/vnd.oasis.opendocument.chart";
    _typesMap["odf"] = "application/vnd.oasis.opendocument.formula";
    _typesMap["odg"] = "application/vnd.oasis.opendocument.graphics";
    _typesMap["odh"] = "text/plain";
    _typesMap["odi"] = "application/vnd.oasis.opendocument.image";
    _typesMap["odl"] = "text/plain";
    _typesMap["odm"] = "application/vnd.oasis.opendocument.text-master";
    _typesMap["odp"] = "application/vnd.oasis.opendocument.presentation";
    _typesMap["ods"] = "application/vnd.oasis.opendocument.spreadsheet";
    _typesMap["odt"] = "application/vnd.oasis.opendocument.text";
    _typesMap["oga"] = "audio/ogg";
    _typesMap["ogg"] = "audio/ogg";
    _typesMap["ogv"] = "video/ogg";
    _typesMap["ogx"] = "application/ogg";
    _typesMap["one"] = "application/onenote";
    _typesMap["onea"] = "application/onenote";
    _typesMap["onepkg"] = "application/onenote";
    _typesMap["onetmp"] = "application/onenote";
    _typesMap["onetoc"] = "application/onenote";
    _typesMap["onetoc2"] = "application/onenote";
    _typesMap["opus"] = "audio/ogg";
    _typesMap["orderedtest"] = "application/xml";
    _typesMap["osdx"] = "application/opensearchdescription+xml";
    _typesMap["otf"] = "application/font-sfnt";
    _typesMap["otg"] = "application/vnd.oasis.opendocument.graphics-template";
    _typesMap["oth"] = "application/vnd.oasis.opendocument.text-web";
    _typesMap["otp"] = "application/vnd.oasis.opendocument.presentation-template";
    _typesMap["ots"] = "application/vnd.oasis.opendocument.spreadsheet-template";
    _typesMap["ott"] = "application/vnd.oasis.opendocument.text-template";
    _typesMap["oxps"] = "application/oxps";
    _typesMap["oxt"] = "application/vnd.openofficeorg.extension";
    _typesMap["p10"] = "application/pkcs10";
    _typesMap["p12"] = "application/x-pkcs12";
    _typesMap["p7b"] = "application/x-pkcs7-certificates";
    _typesMap["p7c"] = "application/pkcs7-mime";
    _typesMap["p7m"] = "application/pkcs7-mime";
    _typesMap["p7r"] = "application/x-pkcs7-certreqresp";
    _typesMap["p7s"] = "application/pkcs7-signature";
    _typesMap["pages"] = "application/vnd.apple.pages";
    _typesMap["pbm"] = "image/x-portable-bitmap";
    _typesMap["pcast"] = "application/x-podcast";
    _typesMap["pct"] = "image/pict";
    _typesMap["pcx"] = "application/octet-stream";
    _typesMap["pcz"] = "application/octet-stream";
    _typesMap["pdf"] = "application/pdf";
    _typesMap["pfb"] = "application/octet-stream";
    _typesMap["pfm"] = "application/octet-stream";
    _typesMap["pfx"] = "application/x-pkcs12";
    _typesMap["pgm"] = "image/x-portable-graymap";
    _typesMap["pic"] = "image/pict";
    _typesMap["pict"] = "image/pict";
    _typesMap["pkgdef"] = "text/plain";
    _typesMap["pkgundef"] = "text/plain";
    _typesMap["pko"] = "application/vnd.ms-pki.pko";
    _typesMap["pls"] = "audio/scpls";
    _typesMap["pma"] = "application/x-perfmon";
    _typesMap["pmc"] = "application/x-perfmon";
    _typesMap["pml"] = "application/x-perfmon";
    _typesMap["pmr"] = "application/x-perfmon";
    _typesMap["pmw"] = "application/x-perfmon";
    _typesMap["png"] = "image/png";
    _typesMap["pnm"] = "image/x-portable-anymap";
    _typesMap["pnt"] = "image/x-macpaint";
    _typesMap["pntg"] = "image/x-macpaint";
    _typesMap["pnz"] = "image/png";
    _typesMap["pot"] = "application/vnd.ms-powerpoint";
    _typesMap["potm"] = "application/vnd.ms-powerpoint.template.macroEnabled.12";
    _typesMap["potx"] = "application/vnd.openxmlformats-officedocument.presentationml.template";
    _typesMap["ppa"] = "application/vnd.ms-powerpoint";
    _typesMap["ppam"] = "application/vnd.ms-powerpoint.addin.macroEnabled.12";
    _typesMap["ppm"] = "image/x-portable-pixmap";
    _typesMap["pps"] = "application/vnd.ms-powerpoint";
    _typesMap["ppsm"] = "application/vnd.ms-powerpoint.slideshow.macroEnabled.12";
    _typesMap["ppsx"] = "application/vnd.openxmlformats-officedocument.presentationml.slideshow";
    _typesMap["ppt"] = "application/vnd.ms-powerpoint";
    _typesMap["pptm"] = "application/vnd.ms-powerpoint.presentation.macroEnabled.12";
    _typesMap["pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
    _typesMap["prf"] = "application/pics-rules";
    _typesMap["prm"] = "application/octet-stream";
    _typesMap["prx"] = "application/octet-stream";
    _typesMap["ps"] = "application/postscript";
    _typesMap["psc1"] = "application/PowerShell";
    _typesMap["psd"] = "application/octet-stream";
    _typesMap["psess"] = "application/xml";
    _typesMap["psm"] = "application/octet-stream";
    _typesMap["psp"] = "application/octet-stream";
    _typesMap["pst"] = "application/vnd.ms-outlook";
    _typesMap["pub"] = "application/x-mspublisher";
    _typesMap["pwz"] = "application/vnd.ms-powerpoint";
    _typesMap["qht"] = "text/x-html-insertion";
    _typesMap["qhtm"] = "text/x-html-insertion";
    _typesMap["qt"] = "video/quicktime";
    _typesMap["qti"] = "image/x-quicktime";
    _typesMap["qtif"] = "image/x-quicktime";
    _typesMap["qtl"] = "application/x-quicktimeplayer";
    _typesMap["qxd"] = "application/octet-stream";
    _typesMap["ra"] = "audio/x-pn-realaudio";
    _typesMap["ram"] = "audio/x-pn-realaudio";
    _typesMap["rar"] = "application/x-rar-compressed";
    _typesMap["ras"] = "image/x-cmu-raster";
    _typesMap["rat"] = "application/rat-file";
    _typesMap["rc"] = "text/plain";
    _typesMap["rc2"] = "text/plain";
    _typesMap["rct"] = "text/plain";
    _typesMap["rdlc"] = "application/xml";
    _typesMap["reg"] = "text/plain";
    _typesMap["resx"] = "application/xml";
    _typesMap["rf"] = "image/vnd.rn-realflash";
    _typesMap["rgb"] = "image/x-rgb";
    _typesMap["rgs"] = "text/plain";
    _typesMap["rm"] = "application/vnd.rn-realmedia";
    _typesMap["rmi"] = "audio/mid";
    _typesMap["rmp"] = "application/vnd.rn-rn_music_package";
    _typesMap["rmvb"] = "application/vnd.rn-realmedia-vbr";
    _typesMap["roff"] = "application/x-troff";
    _typesMap["rpm"] = "audio/x-pn-realaudio-plugin";
    _typesMap["rqy"] = "text/x-ms-rqy";
    _typesMap["rtf"] = "application/rtf";
    _typesMap["rtx"] = "text/richtext";
    _typesMap["rvt"] = "application/octet-stream";
    _typesMap["ruleset"] = "application/xml";
    _typesMap["s"] = "text/plain";
    _typesMap["safariextz"] = "application/x-safari-safariextz";
    _typesMap["scd"] = "application/x-msschedule";
    _typesMap["scr"] = "text/plain";
    _typesMap["sct"] = "text/scriptlet";
    _typesMap["sd2"] = "audio/x-sd2";
    _typesMap["sdp"] = "application/sdp";
    _typesMap["sea"] = "application/octet-stream";
    _typesMap["searchConnector-ms"] = "application/windows-search-connector+xml";
    _typesMap["setpay"] = "application/set-payment-initiation";
    _typesMap["setreg"] = "application/set-registration-initiation";
    _typesMap["settings"] = "application/xml";
    _typesMap["sgimb"] = "application/x-sgimb";
    _typesMap["sgml"] = "text/sgml";
    _typesMap["sh"] = "application/x-sh";
    _typesMap["shar"] = "application/x-shar";
    _typesMap["shtml"] = "text/html";
    _typesMap["sit"] = "application/x-stuffit";
    _typesMap["sitemap"] = "application/xml";
    _typesMap["skin"] = "application/xml";
    _typesMap["skp"] = "application/x-koan";
    _typesMap["sldm"] = "application/vnd.ms-powerpoint.slide.macroEnabled.12";
    _typesMap["sldx"] = "application/vnd.openxmlformats-officedocument.presentationml.slide";
    _typesMap["slk"] = "application/vnd.ms-excel";
    _typesMap["sln"] = "text/plain";
    _typesMap["slupkg-ms"] = "application/x-ms-license";
    _typesMap["smd"] = "audio/x-smd";
    _typesMap["smi"] = "application/octet-stream";
    _typesMap["smx"] = "audio/x-smd";
    _typesMap["smz"] = "audio/x-smd";
    _typesMap["snd"] = "audio/basic";
    _typesMap["snippet"] = "application/xml";
    _typesMap["snp"] = "application/octet-stream";
    _typesMap["sql"] = "application/sql";
    _typesMap["sol"] = "text/plain";
    _typesMap["sor"] = "text/plain";
    _typesMap["spc"] = "application/x-pkcs7-certificates";
    _typesMap["spl"] = "application/futuresplash";
    _typesMap["spx"] = "audio/ogg";
    _typesMap["src"] = "application/x-wais-source";
    _typesMap["srf"] = "text/plain";
    _typesMap["SSISDeploymentManifest"] = "text/xml";
    _typesMap["ssm"] = "application/streamingmedia";
    _typesMap["sst"] = "application/vnd.ms-pki.certstore";
    _typesMap["stl"] = "application/vnd.ms-pki.stl";
    _typesMap["sv4cpio"] = "application/x-sv4cpio";
    _typesMap["sv4crc"] = "application/x-sv4crc";
    _typesMap["svc"] = "application/xml";
    _typesMap["svg"] = "image/svg+xml";
    _typesMap["swf"] = "application/x-shockwave-flash";
    _typesMap["step"] = "application/step";
    _typesMap["stp"] = "application/step";
    _typesMap["t"] = "application/x-troff";
    _typesMap["tar"] = "application/x-tar";
    _typesMap["tcl"] = "application/x-tcl";
    _typesMap["testrunconfig"] = "application/xml";
    _typesMap["testsettings"] = "application/xml";
    _typesMap["tex"] = "application/x-tex";
    _typesMap["texi"] = "application/x-texinfo";
    _typesMap["texinfo"] = "application/x-texinfo";
    _typesMap["tgz"] = "application/x-compressed";
    _typesMap["thmx"] = "application/vnd.ms-officetheme";
    _typesMap["thn"] = "application/octet-stream";
    _typesMap["tif"] = "image/tiff";
    _typesMap["tiff"] = "image/tiff";
    _typesMap["tlh"] = "text/plain";
    _typesMap["tli"] = "text/plain";
    _typesMap["toc"] = "application/octet-stream";
    _typesMap["tr"] = "application/x-troff";
    _typesMap["trm"] = "application/x-msterminal";
    _typesMap["trx"] = "application/xml";
    _typesMap["ts"] = "video/vnd.dlna.mpeg-tts";
    _typesMap["tsv"] = "text/tab-separated-values";
    _typesMap["ttf"] = "application/font-sfnt";
    _typesMap["tts"] = "video/vnd.dlna.mpeg-tts";
    _typesMap["txt"] = "text/plain";
    _typesMap["u32"] = "application/octet-stream";
    _typesMap["uls"] = "text/iuls";
    _typesMap["user"] = "text/plain";
    _typesMap["ustar"] = "application/x-ustar";
    _typesMap["vb"] = "text/plain";
    _typesMap["vbdproj"] = "text/plain";
    _typesMap["vbk"] = "video/mpeg";
    _typesMap["vbproj"] = "text/plain";
    _typesMap["vbs"] = "text/vbscript";
    _typesMap["vcf"] = "text/x-vcard";
    _typesMap["vcproj"] = "application/xml";
    _typesMap["vcs"] = "text/plain";
    _typesMap["vcxproj"] = "application/xml";
    _typesMap["vddproj"] = "text/plain";
    _typesMap["vdp"] = "text/plain";
    _typesMap["vdproj"] = "text/plain";
    _typesMap["vdx"] = "application/vnd.ms-visio.viewer";
    _typesMap["vml"] = "text/xml";
    _typesMap["vscontent"] = "application/xml";
    _typesMap["vsct"] = "text/xml";
    _typesMap["vsd"] = "application/vnd.visio";
    _typesMap["vsi"] = "application/ms-vsi";
    _typesMap["vsix"] = "application/vsix";
    _typesMap["vsixlangpack"] = "text/xml";
    _typesMap["vsixmanifest"] = "text/xml";
    _typesMap["vsmdi"] = "application/xml";
    _typesMap["vspscc"] = "text/plain";
    _typesMap["vss"] = "application/vnd.visio";
    _typesMap["vsscc"] = "text/plain";
    _typesMap["vssettings"] = "text/xml";
    _typesMap["vssscc"] = "text/plain";
    _typesMap["vst"] = "application/vnd.visio";
    _typesMap["vstemplate"] = "text/xml";
    _typesMap["vsto"] = "application/x-ms-vsto";
    _typesMap["vsw"] = "application/vnd.visio";
    _typesMap["vsx"] = "application/vnd.visio";
    _typesMap["vtt"] = "text/vtt";
    _typesMap["vtx"] = "application/vnd.visio";
    _typesMap["wasm"] = "application/wasm";
    _typesMap["wav"] = "audio/wav";
    _typesMap["wave"] = "audio/wav";
    _typesMap["wax"] = "audio/x-ms-wax";
    _typesMap["wbk"] = "application/msword";
    _typesMap["wbmp"] = "image/vnd.wap.wbmp";
    _typesMap["wcm"] = "application/vnd.ms-works";
    _typesMap["wdb"] = "application/vnd.ms-works";
    _typesMap["wdp"] = "image/vnd.ms-photo";
    _typesMap["webarchive"] = "application/x-safari-webarchive";
    _typesMap["webm"] = "video/webm";
    _typesMap["webp"] = "image/webp";
    _typesMap["webtest"] = "application/xml";
    _typesMap["wiq"] = "application/xml";
    _typesMap["wiz"] = "application/msword";
    _typesMap["wks"] = "application/vnd.ms-works";
    _typesMap["WLMP"] = "application/wlmoviemaker";
    _typesMap["wlpginstall"] = "application/x-wlpg-detect";
    _typesMap["wlpginstall3"] = "application/x-wlpg3-detect";
    _typesMap["wm"] = "video/x-ms-wm";
    _typesMap["wma"] = "audio/x-ms-wma";
    _typesMap["wmd"] = "application/x-ms-wmd";
    _typesMap["wmf"] = "application/x-msmetafile";
    _typesMap["wml"] = "text/vnd.wap.wml";
    _typesMap["wmlc"] = "application/vnd.wap.wmlc";
    _typesMap["wmls"] = "text/vnd.wap.wmlscript";
    _typesMap["wmlsc"] = "application/vnd.wap.wmlscriptc";
    _typesMap["wmp"] = "video/x-ms-wmp";
    _typesMap["wmv"] = "video/x-ms-wmv";
    _typesMap["wmx"] = "video/x-ms-wmx";
    _typesMap["wmz"] = "application/x-ms-wmz";
    _typesMap["woff"] = "application/font-woff";
    _typesMap["woff2"] = "application/font-woff2";
    _typesMap["wpl"] = "application/vnd.ms-wpl";
    _typesMap["wps"] = "application/vnd.ms-works";
    _typesMap["wri"] = "application/x-mswrite";
    _typesMap["wrl"] = "x-world/x-vrml";
    _typesMap["wrz"] = "x-world/x-vrml";
    _typesMap["wsc"] = "text/scriptlet";
    _typesMap["wsdl"] = "text/xml";
    _typesMap["wvx"] = "video/x-ms-wvx";
    _typesMap["x"] = "application/directx";
    _typesMap["xaf"] = "x-world/x-vrml";
    _typesMap["xaml"] = "application/xaml+xml";
    _typesMap["xap"] = "application/x-silverlight-app";
    _typesMap["xbap"] = "application/x-ms-xbap";
    _typesMap["xbm"] = "image/x-xbitmap";
    _typesMap["xdr"] = "text/plain";
    _typesMap["xht"] = "application/xhtml+xml";
    _typesMap["xhtml"] = "application/xhtml+xml";
    _typesMap["xla"] = "application/vnd.ms-excel";
    _typesMap["xlam"] = "application/vnd.ms-excel.addin.macroEnabled.12";
    _typesMap["xlc"] = "application/vnd.ms-excel";
    _typesMap["xld"] = "application/vnd.ms-excel";
    _typesMap["xlk"] = "application/vnd.ms-excel";
    _typesMap["xll"] = "application/vnd.ms-excel";
    _typesMap["xlm"] = "application/vnd.ms-excel";
    _typesMap["xls"] = "application/vnd.ms-excel";
    _typesMap["xlsb"] = "application/vnd.ms-excel.sheet.binary.macroEnabled.12";
    _typesMap["xlsm"] = "application/vnd.ms-excel.sheet.macroEnabled.12";
    _typesMap["xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
    _typesMap["xlt"] = "application/vnd.ms-excel";
    _typesMap["xltm"] = "application/vnd.ms-excel.template.macroEnabled.12";
    _typesMap["xltx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.template";
    _typesMap["xlw"] = "application/vnd.ms-excel";
    _typesMap["xml"] = "text/xml";
    _typesMap["xmp"] = "application/octet-stream";
    _typesMap["xmta"] = "application/xml";
    _typesMap["xof"] = "x-world/x-vrml";
    _typesMap["XOML"] = "text/plain";
    _typesMap["xpm"] = "image/x-xpixmap";
    _typesMap["xps"] = "application/vnd.ms-xpsdocument";
    _typesMap["xrm-ms"] = "text/xml";
    _typesMap["xsc"] = "application/xml";
    _typesMap["xsd"] = "text/xml";
    _typesMap["xsf"] = "text/xml";
    _typesMap["xsl"] = "text/xml";
    _typesMap["xslt"] = "text/xml";
    _typesMap["xsn"] = "application/octet-stream";
    _typesMap["xss"] = "application/xml";
    _typesMap["xspf"] = "application/xspf+xml";
    _typesMap["xtp"] = "application/octet-stream";
    _typesMap["xwd"] = "image/x-xwindowdump";
    _typesMap["z"] = "application/x-compress";
    _typesMap["zip"] = "application/zip";
}