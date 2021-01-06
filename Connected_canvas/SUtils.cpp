#include "SUtils.h"

SUtils::SUtils()
{
}

SUtils* SUtils::instance = 0;

void SUtils::newRequest()
{
  QString lGitHubURL{"https://api.github.com/repos/Mitsuriou/MFBO-Preset-Creator/releases/latest"};
  HTTPDownloader* lHTTPDownloader{new HTTPDownloader(lGitHubURL, this)};
  this->connect(lHTTPDownloader, &HTTPDownloader::resultReady, this, &Update::pageFetched);
  this->connect(lHTTPDownloader, &HTTPDownloader::finished, lHTTPDownloader, &QObject::deleteLater);
  lHTTPDownloader->start();
}
