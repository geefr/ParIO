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
    stage('CMake') { steps {
      dir("${env.WORKSPACE}/build") {
sh returnStdout: true, script: '''echo $PWD'''
//        sh returnStdout: true, script:  '''cmake -DCMAKE_INSTALL_PREFIX="${env.WORKSPACE}/install" "${env.WORKSPACE}/source"'''
      }
    } }
    stage('Build') {
      steps {
        dir("${env.WORKSPACE}/build") {
sh returnStdout: true, script:  '''make install'''
        }
      }
    }
    stage('Package') {
      steps {
        sh "tar -cvzf ${env.WORKSPACE}/ParIO.tar.gz ${env.WORKSPACE}/install/*"

archiveArtifacts artifacts: '${env.WORKSPACE}/ParIO.tar.gz', fingerprint: true, onlyIfSuccessful: true
      }
    }
  }
}
