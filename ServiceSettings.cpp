///////////////////////////////////////////////////////////
//  ServiceSettings.cpp
//  Implementation of the Class ServiceSettings
//  Created on:      30-Sau-2014 17:06:18
//  Original author: Povilas
///////////////////////////////////////////////////////////
#define _ELPP_THREAD_SAFE
#define _ELPP_STL_LOGGING
#define _ELPP_NO_DEFAULT_LOG_FILE

#include "ServiceSettings.h"
#include "ErrorResponse.h"
#include "HelperMethods.h"
#include "logging/easylogging++.h"
#include <string>
#include <limits.h>
#include <unistd.h>
#include <fstream>
#include <sstream>

ServiceSettings::ServiceSettings()
{
}

ServiceSettings::~ServiceSettings(){

}

/*bool ServiceSettings::decodeUserFile(std::string uID, InitDamisService *dFile)
{
    bool returnState = false;
    LOG(INFO)<<"Secure connection requested by -->"<< uID;
    std::string uPath = ServiceSettings::pathToCertificates;
    std::string uFile = ServiceSettings::getUserCertificate(uID);
    ;

    if (!uFile.empty() && !uPath.empty())
    {
        std::string fileToCnvert = dFile->getFilePath();

        std::ifstream file(uPath + uFile);
        if (!file.good())
        {
             LOG(ERROR)<<"User certificate file not found. Contact administrator. Aborting.";
             ErrorResponse::setFaultDetail("Cannot find user" + uID + " private key certificate file " + uFile);
             file.close();ll
             return false;
        }
        else
        {
            file.close();
            std::string stringToProcess = "openssl smime -decrypt -in " + fileToCnvert;
            stringToProcess.append(" -binary -inform DEM -inkey " + uFile + " -out " + dFile->getFilePath() +  ".out");

            system(stringToProcess.c_str());

        }

       //decrypt file

        returnState = true;
    }
    return returnState;

}
std::string ServiceSettings::getUserCertificate(std::string uID)
{
    LOG(INFO)<<"Checking user certificate";
    std::string certificateFile = "";
    std::ifstream file(ServiceSettings::pathToUserConfig);
    std::string line_from_file;
    std::string tmp1;

     if (file.good())
    {
        while (std::getline(file, line_from_file))
        {
            if (line_from_file.length() == 0)
            {
                continue;
            }
            std::istringstream iss(line_from_file);
            std::string sub;
            iss >> sub;
            if (sub == "%")
            {
                continue;
            }
            else
            {
              iss >> tmp1;
                if (sub == uID)
                {
                    certificateFile = tmp1;
                    LOG(INFO) << "User in secure user list has been found";
                    break;
                }
            }
        }
    }
    else
    {
        ErrorResponse::setFaultDetail("User unknown");
        LOG(ERROR) << "User " <<uID << " is unknown. No record in usres.conf";
    }

    file.close();
    return certificateFile;
}*/

std::string ServiceSettings::getExePath()
{
  char result[ PATH_MAX ];
  ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
  std::string path;
  if (count !=-1)
    result[count] = 0;
    path = result;

   std::string::size_type t = path.find_last_of("/");
   path = path.substr(0,t) + "/";

  return path; //std::string( path, (count > 0) ? count : 0 );
}

bool ServiceSettings::initialize()
{
    std::string oFile = ServiceSettings::getExePath();
    oFile+="settings.csv";
    std::string line_from_file;
    std::string tmp1, tmp2, tmp3;
    int line_no;

    std::ifstream file(oFile);

    if (file.good())
    {
        while (std::getline(file, line_from_file))
        {
            if (line_from_file.length() == 0)
            {
                line_no++;
                continue;
            }
            std::istringstream iss(line_from_file);
            std::string sub;
            iss >> sub;
            if (sub == "%")
            {
                line_no++;
                continue;
            }
            else
            {
              iss >> tmp1;
                if (sub == "wsdlPath")
                    ServiceSettings::wsdlPath = tmp1;
                else if (sub == "logingConfFilePath")
                    ServiceSettings::logingConfFilePath = tmp1;
                else if (sub == "pathToAlgorithmsExe")
                    ServiceSettings::pathToAlgorithmsExe = tmp1;
                else if (sub == "localDataFileSavePath")
                    ServiceSettings::localDataFileSavePath  = tmp1;
                else if (sub == "httpDataFileSavePath")
                    ServiceSettings::httpDataFileSavePath  = tmp1;
                else if (sub == "dataFileExtension")
                    ServiceSettings::dataFileExtension  = tmp1;
                else if (sub == "lenghtOfTmpFileName")
                    ServiceSettings::lenghtOfTmpFileName  = HelperMethods::strToInt(tmp1);
                else if (sub == "keepFilesInDirectory")
                    ServiceSettings::keepFilesInDirectory  = HelperMethods::strToInt(tmp1);
                else if (sub == "noOfProcessors")
                    ServiceSettings::noOfProcessors  = HelperMethods::strToInt(tmp1);
                else if (sub == "runDestination")
                    ServiceSettings::runDestination  = HelperMethods::strToInt(tmp1);
                else if (sub == "pathToMPIExecutable")
                    ServiceSettings::pathToMPIExecutable  = tmp1;
                else if (sub == "workingDirMPI")
                    ServiceSettings::workingDirMPI  = tmp1;
              /*  else if (sub == "pathToUserConfig")
                    ServiceSettings::pathToUserConfig = tmp1;
                else if (sub == "pathToCertificates")
                    ServiceSettings::pathToCertificates = tmp1;*/

            }
		// std::cout << tmp1;
        }
    file.close();
    return true;
    }
    else
    {
        ErrorResponse::setFaultDetail("Cannot find file settings.csv in working directory.");
        LOG(WARNING) << "Cannot find file settings.csv in working directory";
        file.close();
        return false;
    }


}

//Debug DAMIS
	//std::string ServiceSettings::wsdlPath = "C:/inetpub/wwwroot/Damis/TestDamis.wsdl";
	//std::string ServiceSettings::wsdlPath = "/var/www/damis/TestDamis.wsdl";
	//std::string ServiceSettings::logingConfFilePath = "C:/inetpub/wwwroot/Damis/cgi-bin/testlogging.conf";
	//std::string ServiceSettings::logingConfFilePath ="/var/www/damis/cgi-bin/TestLogging.conf";
    //std::string ServiceSettings::pathToAlgorithmsExe = "\"D:/Povilas Data/My Documents/CodeBlocks/ClusterAlgorithms/bin/Debug/ClusterAlgorithms.exe\"";
    //std::string ServiceSettings::pathToAlgorithmsExe = "/Home/Povilas/Documents/C++/Algorithms/bin/Debug/Algorithms";

//*/

//Release DAMIS
/*	std::string ServiceSettings::wsdlPath = "C:/inetpub/wwwroot/Damis/Damis.wsdl";
//	std::string ServiceSettings::logingConfFilePath = "C:/inetpub/wwwroot/Damis/cgi-bin/logging.conf";
	std::string ServiceSettings::pathToAlgorithmsExe = "\"D:/Povilas Data/My Documents/CodeBlocks/ClusterAlgorithms/bin/Release/ClusterAlgorithms.exe\"";
//*/

	std::string ServiceSettings::wsdlPath = "/users3/virginijus/www/Damis/apache/htdocs/Damis.wsdl";

	std::string ServiceSettings::pathToAlgorithmsExe = "/scratch/lustre/home/virginijus/exec/Algorithms/";

	std::string ServiceSettings::localDataFileSavePath = "/scratch/lustre/home/virginijus/data/";

	std::string ServiceSettings::logingConfFilePath = "/scratch/lustre/home/virginijus/exec/DamisService/Logging.conf";

	std::string ServiceSettings::httpDataFileSavePath = "http://damis.lt:8087/data/";

	std::string ServiceSettings::dataFileExtension = ".arff";

	int ServiceSettings::lenghtOfTmpFileName = 20;

	int ServiceSettings::keepFilesInDirectory = 2*24*60*60;

	int ServiceSettings::noOfProcessors = 128;

	int ServiceSettings::runDestination = 2;

	std::string ServiceSettings::pathToMPIExecutable = "mpirun";

	std::string ServiceSettings::workingDirMPI = "/scratch/lustre/home/virginijus/data/";

	/*std::string ServiceSettings::pathToCertificates = "/home/damis/apache/htdocs/damis/certificates/";
	std::string ServiceSettings::pathToUserConfig  = "/home/damis/exec/DamisService/bin/Debug/users.conf";*/


