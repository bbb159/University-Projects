package application.threads;

import application.helper.DataStorage;
import application.helper.FileStorageHelper;
import application.model.Operacao;

import java.util.List;

public class ThreadLogger extends Thread {

    private static final String FILE_NAME = "server_log.txt";

    private static ThreadLogger threadLogger;
    private static FileStorageHelper fileStorageHelper;

    private ThreadLogger(){
        fileStorageHelper = new FileStorageHelper(FILE_NAME);
    }

    static ThreadLogger init() {
        if(threadLogger == null) {
            threadLogger = new ThreadLogger();
            threadLogger.start();
        }
        return threadLogger;
    }

    static void clearLog() {
        if(fileStorageHelper != null) {
            fileStorageHelper.clearFile();
        }
    }

    @Override
    public void run(){
        while(true) {
            if(!DataStorage.getInstance().getLog().isEmpty()) {

                Operacao op = DataStorage.getInstance().pollLog();
                updateLogFile(op);
            }
        }
    }

    private void updateLogFile(Operacao operacao) {
        fileStorageHelper.saveLogData(operacao);
    }

    List<Operacao> getLogList() {
        return fileStorageHelper.recoverListData();
    }
}
