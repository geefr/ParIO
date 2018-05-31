pipeline {
  agent any

  options {
    buildDiscarder( logRotator(artifactDaysToKeepStr: '90') )
    checkoutToSubdirectory('source')
    timeout(time: 1, unit: 'HOURS')
  }
  triggers { 
    pollSCM('H * * * *') 
  }

  stages {
    stage('Build') {
      steps {
sh returnStatus: true, script: '''mkdir build
mkdir install
cd build
cmake -DCMAKE_INSTALL_PREFIX=${env.WORKSPACE}/install ${env.WORKSPACE}/source
make install
cd ${env.WORKSPACE}
tar -cvzf ${env.WORKSPACE}/ParIO.tar.gz ${env.WORKSPACE}/install/*'''
      }
    }
  }
}
